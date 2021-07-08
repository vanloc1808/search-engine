#pragma once
#include <string>

struct fileData {
	string filePath;
	double value; //the value of expression tf * idf
	int intersectionCount;
};


struct folderData {
	string folderName;
	IDF_list idf;
	TF_list* tfArr;
	fileData* files;
	int nFiles;
};

void initFolderStruct(folderData& data);
void initFileStruct(fileData& data);

void saveFolderStruct(folderData& data, string name, IDF_list idf, TF_list* tfArr);
void saveFileStruct(fileData& data, string path, double value, int cnt);

void firstSearch(string key, folderData*& folderList, string** fileList, int nFolders);

void sortFileData(fileData* fileStructArr);

void printResult(fileData* fileStructArr);

void inputProcess(string input, fileData* fileStructArr, string** fileList, int nFolders);
