#pragma once
#include <string>
#include "TF.h"
#include "IDF.h"
using namespace std;

struct FileData {
	int posFolder;
	int posFile;
	double value; //the value of expression tf * idf
	int intersectionCount;
};

struct FolderData {
	IDF_list idfL;
	TF_list* tfLArr;
};

struct ResponseData {
	FileData* file;
	int size;
	int cap;
};

// --------------StringArray----------------

struct StringArray {
	string* array;
	int size;
	int cap;
};

void initString(StringArray&);
void addString(StringArray&, string);
void deleteArray(StringArray&);
void loadTextToArray(StringArray&, const string&);

// --------------File----------------------

void makeFolderWrapper(const string&);
void getFolderWrapper(const string&, const string&);
void getFileWrapper(const string&, const string&);
void deleteFileWrapper(const string&);
string extractPath(string);

void copyFolderWrapper(const string&, const string&);
void openFileWithNotepadWrapper(const string&);

// --------------Miscellaneous--------------

void evalCommand(const string&);
void sortMultiThread(StringArray&);
int bSearchTF(TF_list, const string&);
int bSearchIDF(IDF_list List, const string& Key);

// -----------------------------------------
void initResponse(ResponseData &);
void addResponse(ResponseData &, FileData);
void deleteResponse(ResponseData &);
void intersectResponse(ResponseData &, ResponseData);
void sortResponse(ResponseData &);