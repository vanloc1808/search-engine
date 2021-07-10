#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define METADATA_NAME "metadata"

#define SUBFOLDER_NAME "FolderList.txt"

#define INDEX_NAME "Index.txt"

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <fstream>
#include <codecvt>
#include <sstream>
#include "Normalizer.h"
#include "FileProgression.h"
#include "TF.h"
#include "IDF.h"
#include "Utility.h"

using namespace std;

StringArray strArr;

string* folderList = nullptr;
int folderCount = 0;

string** fileList = nullptr;
int* fileCount = nullptr;

folderData* folder_data;

void prepareFile(string folderPath)
{
	makeFolderWrapper(METADATA_NAME);
	getFolderWrapper(folderPath, SUBFOLDER_NAME);
	
	ifstream input(SUBFOLDER_NAME, ios::in);

	string line = "";
	while (getline(input, line))
	{
		string path_to_folder = folderPath + "\\" + line;
		string path_to_file = string(METADATA_NAME) + "\\" + line + ".txt";
		getFileWrapper(path_to_folder, path_to_file);
		makeFolderWrapper(string(METADATA_NAME) + "\\" + line);
	}

	input.close();
}

TF_list createTF(string filePath) {
	TF_list L;
	TFListInit(L);
	wifstream fin(filePath, ios::in);
	fin.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
	wstring s;

	while (fin >> s) {
		string convertedString = VEconvert(s);
		if (convertedString.length() == 0)
			continue;
		addString(strArr, convertedString);
	}

	sort_multiThread(strArr);
	TFList_Input(L, strArr.Array, strArr.size);
	fin.close();
	strArr.size = 0; // reset but not free
	return L;
}

void createMetadata(string folderDataset) 
{
	initString(strArr);
	prepareFile(folderDataset);

	ifstream subFol(SUBFOLDER_NAME, ios::in);
	string folderName = "";

	while (getline(subFol, folderName)) 
	{
		cout << "Processing with folder " << folderName << "...\n";
		int nFiles = 0;
		string listFile = string("" METADATA_NAME "\\") + folderName + ".txt";
		ifstream fr(listFile, ios::in);
		string fileName = "";

		while (getline(fr, fileName)) 
		{
			nFiles++;
			string tfPath = string("" METADATA_NAME "\\") + folderName + '\\' + fileName + ".tf";
			string filePath = folderDataset + "\\" + folderName + "\\" + fileName;
			TF_list L = createTF(filePath);
			SaveTFList((char*)tfPath.c_str(), L);
			FreeTFList(L);
		}
		fr.close();

		string path = string("" METADATA_NAME "\\") + folderName;
		IDF_list idf = createIDF(path);
		string idfPath = path + string(".idf");
		SaveIDFList((char*)idfPath.c_str(), idf);
		FreeIDFList(idf);
	}
	subFol.close();

	deleteArray(strArr);
}

void loadToRAM()
{
	initString(strArr);

	loadTextToArray(strArr, SUBFOLDER_NAME);

	folderCount = strArr.size;
	folderList = new string[folderCount];
	fileList = new string*[folderCount];
	fileCount = new int[folderCount];

	folder_data = new folderData[folderCount];

	for(int i = 0; i < folderCount; i++)
		folderList[i] = strArr.Array[i];

	strArr.size = 0;

	for(int i = 0; i < folderCount; i++)
	{
		string filePath = string(METADATA_NAME) + "\\" + folderList[i];
		loadTextToArray(strArr, filePath + ".txt");
		
		LoadIDFList(filePath + ".idf", folder_data[i].idfL);
		folder_data[i].tfLArr = new TF_list[strArr.size];

		fileCount[i] = strArr.size;
		fileList[i] = new string[strArr.size];

		for(int j = 0; j < strArr.size; j++)
		{
			fileList[i][j] = strArr.Array[j];
			LoadTFList(filePath + "\\" + strArr.Array[j] + ".tf", folder_data[i].tfLArr[j]);
		}
	}

	deleteArray(strArr);
}

ResponseData queryRequest(string word) // singular word
{
	int posIDF = 0;
	int posTF = 0;

	double idfValue = 0.f;
	double tfValue = 0.f;

	ResponseData rd;
	initResponse(rd);

	for(int i = 0; i < folderCount; i++) 
	{
		if((posIDF = bSearch_IDF(folder_data[i].idfL, word)) != -1) // If found
		{
			idfValue = getIDFValue(folder_data[i].idfL, posIDF);
			for(int j = 0; j < fileCount[i]; j++)
			{
				if((posTF = bSearch_TF(folder_data[i].tfLArr[j], word)) != -1)
				{
					tfValue = getTFValue(folder_data[i].tfLArr[j], posTF);
					addResponse(rd, fileData{i, j, idfValue * tfValue, 1});
				}
			}
		}
	}
	return rd;
}

IDF_list createIDF(string folderPath) 
{
	string directory = folderPath + ".txt"; // for example, metadata\Am nhac -> metadata\Am nhac.txt
	string fileName = "";
	ifstream path(directory, ios::in);
	
	strArr.size = 0;

	IDF_list idfL;
	IDFListInit(idfL);

	int nFiles= 0;// number of files
	int nWords = 0; //number of words

	while (getline(path, fileName)) 
	{
		if (fileName.length() == 0) 
			continue;
		nFiles++;

		string tfPath = folderPath + "\\" + fileName + ".tf";

		TF_list tfL;
		LoadTFList(tfPath, tfL);

		for (int i = 0; i < tfL.size; i++) 
		{
			string tempStr = tfL.arrNorm[i].word;
			if (tempStr.length() == 0) 
				continue;
			nWords++;

			addString(strArr, tempStr);
		}
		FreeTFList(tfL);
	}

	sort_multiThread(strArr);
	IDFList_Input(idfL, nFiles, strArr.Array, nWords);
	path.close();
	strArr.size = 0;

	return idfL;
}

void test(string key) {
	ResponseData res = queryRequest(key);
	sortResponse(res);
	fileData* listRes = res.file;
	int size = res.size;
	for (int i = 0; i < size; i++) {
		fileData thisFile = listRes[i];
		cout << fileList[thisFile.posFolder][thisFile.posFile] << " in folder " << folderList[thisFile.posFolder] << ". ";
		cout << "The value is: " << thisFile.value << "\n";
	}
}

int findMaxSize(ResponseData* respArr, int arrSize) {
	ResponseData res = respArr[0];
	int idx = 0;
	for (int i = 1; i < arrSize; i++) {
		ResponseData thisRes = respArr[i];
		if (res.size < thisRes.size) {
			res = thisRes;
			idx = i;
		}
	}
	return idx;
}

void searchSentence(string sentence) {
	istringstream oss(sentence);
	string temp;
	StringArray stringArr;
	initString(stringArr);
	while (oss >> temp) {
		addString(stringArr,temp);
	}
	int size = stringArr.size;
	ResponseData* resResponse = new ResponseData[size];
	for (int i = 0; i < size; i++) {
		resResponse[i] = queryRequest(stringArr.Array[i]);
	}
	int maxIndex = findMaxSize(resResponse, size);
	ResponseData rd = resResponse[maxIndex];
	for (int i = 0; i < size; i++) {
		if (i == maxIndex) {
			continue;
		}
		intersectResponse(rd, resResponse[i]);
	}
	sortResponse(rd);
	int resSize = rd.size;
	fileData* resFiles = rd.file;
	if (resSize > 20) {
		resSize = 20;
	}
	for (int i = 0; i < resSize; i++) {
		fileData thisFile = resFiles[i];
		cout << fileList[thisFile.posFolder][thisFile.posFile] << " in folder " << folderList[thisFile.posFolder] << ". ";
		//cout << "The value is: " << thisFile.value << ". ";
		cout << "Fit " << thisFile.intersectionCount << " words.\n";
	}
	delete[]resResponse;
	deleteArray(stringArr);
}

