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

double getIDFValue(IDF_list, int);

void idfListInit(IDF_list&);
void addIDF(IDF_list&, IDF);
void loadIDFList(const string&, IDF_list&);
void saveIDFList(const string&, IDF_list);
void freeIDFList(IDF_list&);

void idfListInput(IDF_list&, int, string*, int);