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

void IDFListInit(IDF_list&);
void addIDF(IDF_list&, IDF);
void LoadIDFList(char*, IDF_list&);
void SaveIDFList(char*, IDF_list);
void FreeIDFList(IDF_list&);