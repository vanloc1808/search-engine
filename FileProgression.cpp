#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#define METADATA_NAME "metadata"

#define SUBFOLDER_NAME "FolderList.txt"

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <string.h>
#include <fstream>
#include <codecvt>
#include "Normalizer.h"
#include "FileProgression.h"
#include "TF.h"
#include "IDF.h"
#include "Utility.h"
#include "InputProcess.h"

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

// void newFileListToNewFolder(string**& fileList, int nFolders) {
// 	string** temp = new string * [nFolders];
// 	for (int i = 0; i < nFolders - 1; i++) {
// 		temp[i] = fileList[i];
// 	}
// 	delete[]fileList;
// 	fileList = temp;
// }

// void newFileListIfNewFile(string**& fileList, int nFolders, int nFiles) {
// 	string** temp = new string * [nFolders];
// 	for (int i = 0; i < nFolders - 1; i++) {
// 		temp[i] = fileList[i];
// 	}
// 	temp[nFolders - 1] = new string[nFiles];
// 	for (int i = 0; i < nFiles - 1; i++) {
// 		temp[nFolders - 1][i] = fileList[nFolders - 1][i];
// 	}
// 	delete[]fileList;
// 	fileList = temp;
// }

void createMetadata(string folderDataset/*, string**& fileList, int& nFolders*/) 
{
	initString(strArr);
	prepareFile(folderDataset);

	ifstream subFol(SUBFOLDER_NAME, ios::in);
	string folderName = "";
	//fileList = nullptr;
	//nFolders = 0;

	while (getline(subFol, folderName)) 
	{
		//nFolders++;
		//newFileListToNewFolder(fileList, nFolders);
		int nFiles = 0;
		string listFile = string("" METADATA_NAME "\\") + folderName + ".txt";
		ifstream fr(listFile, ios::in);
		string fileName = "";

		while (getline(fr, fileName)) 
		{
			nFiles++;
			//newFileListIfNewFile(fileList, nFolders, nFiles);
			//fileList[nFolders - 1][nFiles - 1] = folderName + '\\' + fileName;
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