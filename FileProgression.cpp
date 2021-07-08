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
#include "Utility.h"

using namespace std;

StringArray strArr;

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
		string listFile = string("" METADATA_NAME "\\") + folderName + ".txt";
		ifstream fr(listFile, ios::in);
		string fileName = "";

		while (getline(fr, fileName)) 
		{
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
		LoadTFList((char*)tfPath.c_str(), tfL);

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