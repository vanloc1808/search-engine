#define _CRT_SECURE_NO_WARNINGS

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
#include <iostream>
#include <stdio.h>
#include "Utility.h"
#include "InputProcess.h"

const int nMaxOfRes = 10;


void initFolderStruct(folderData& data) {
	data.folderName = "";
	IDFListInit(data.idf);
	data.tfArr = nullptr;
	data.nFiles = 0;
}

void initFileStruct(fileData& data) {
	data.filePath = "";
	data.value = 0;
	data.intersectionCount = 0;
}

void saveFolderStruct(folderData& data, string name, IDF_list idf, TF_list* tfArr) {
	data.folderName = name;
	data.idf = idf;
	data.tfArr = tfArr;
}

void saveFileStruct(fileData& data, string path, double value, int cnt) {
	data.filePath = path;
	data.value = value;
	data.intersectionCount = cnt;
}

void firstSearch(string key, folderData*& folderList, string** fileList, int nFolders) {
	for (int i = 0; i < nFolders; i++) {
		double value = 0;
		int cnt = 0;
		string path = "";
		int inIDF = bSearch_IDF(folderList[i].idf, key);
		if (inIDF == -1) {
			continue;
		}
		path += folderList[i].folderName + string("\\");
		for (int j = 0; j < folderList[i].nFiles; j++) {
			int inTF = bSearch_TF(folderList[i].tfArr[j], key);
			if (inTF == -1) {
				continue;
			}
			path += fileList[i][j];
			value += folderList->idf.arrNorm[inIDF].value * folderList[i].tfArr[j].arrNorm[inTF].count;
			cnt++;
			saveFileStruct(folderList[i].files[j], path, value, cnt);
		}
	}
}

void sortFileData(fileData* fileStructArr) {

}

void printResult(fileData* fileStructArr) {
	for (int i = 0; i < nMaxOfRes; i++) {
		cout << fileStructArr[i].filePath << "\n";
	}
}

void inputProcess(string input, fileData* fileStructArr, string** fileList, int nFolders) {
	folderData* folderList = nullptr;
	//how to init this

	fileData* fileStructArr = nullptr;
	//init the array of fileData structs... 

	char delim[] = " -,.!";
	char* token = strtok((char*)input.c_str(), delim);
	while (token) {
		string key = token;
		firstSearch(key, folderList, fileList, nFolders);
		token = strtok(NULL, delim);
	}
	sortFileData(fileStructArr);
	printResult(fileStructArr);
}

