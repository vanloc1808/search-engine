#pragma once
#include <string>
#include "TF.h"
using namespace std;

// --------------StringArray----------------

struct StringArray {
	string* Array;
	int size;
	int cap;
};

void initString(StringArray&);
void addString(StringArray&, string);
void deleteArray(StringArray&);

// --------------File----------------------

void makeFolderWrapper(string);
void getFolderWrapper(string, string);
void getFileWrapper(string, string);
void deleteFileWrapper(string);
string extractPath(string);

// --------------Miscellaneous--------------

void evalCommand(string);
void sort_multiThread(StringArray&);
int bSearch_TF(TF_list, string);
int bSearch_IDF(IDF_list List, string key);