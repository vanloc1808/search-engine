#pragma once
#include <string>
using std::string;

// Word | Value | Name
struct IDF {
	string word;
	double value;
	string name;
};

struct IDF_list {
	int size;
	int capacity;
	IDF* arrNorm;
	IDF* arrTele;
};

void IDFListInit(IDF_list&);
void addIDF(IDF_list&, IDF, bool);
void LoadIDFList(char*, IDF_list&);
void SaveIDFList(char*, IDF_list);
void FreeIDFList(IDF_list&);