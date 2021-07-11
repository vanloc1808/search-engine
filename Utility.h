#pragma once
#include <string>
#include "TF.h"
#include "IDF.h"
using namespace std;

struct fileData {
	int posFolder;
	int posFile;
	double value; //the value of expression tf * idf
	int intersectionCount;
};

struct folderData {
	IDF_list idfL;
	TF_list* tfLArr;
};

struct ResponseData {
	fileData* file;
	int size;
	int cap;
};

// --------------StringArray----------------

struct StringArray {
	string* Array;
	int size;
	int cap;
};

void initString(StringArray&);
void addString(StringArray&, string);
void deleteArray(StringArray&);
void loadTextToArray(StringArray&, string);

// --------------File----------------------

void makeFolderWrapper(string);
void getFolderWrapper(string, string);
void getFileWrapper(string, string);
void deleteFileWrapper(string);
string extractPath(string);

void copyFolderWrapper(string, string);

// --------------Miscellaneous--------------

void evalCommand(string);
void sort_multiThread(StringArray&);
int bSearch_TF(TF_list, string);
int bSearch_IDF(IDF_list List, string key);

// -----------------------------------------
void initResponse(ResponseData &);
void addResponse(ResponseData &, fileData);
void deleteResponse(ResponseData &);
void intersectResponse(ResponseData &, ResponseData);
void sortResponse(ResponseData &);