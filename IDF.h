#pragma once
#include <string>
using std::string;

// Word | Value
struct IDF {
	string word;
	int value;
};

struct IDF_list {
	int size;
	int capacity;
	int numFile;
	IDF* arrNorm;
};

double getIDFValue(IDF_list List, int i);

void IDFListInit(IDF_list&);
void addIDF(IDF_list&, IDF);
void LoadIDFList(string, IDF_list&);
void SaveIDFList(string, IDF_list);
void FreeIDFList(IDF_list&);

void IDFList_Input(IDF_list&, int, string*, int);