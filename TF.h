#pragma once
#include <string>
using std::string;

// word | count
struct TF {
    string word;
    int count;
};

struct TF_list {
	int size;
	int capacity;
	int totalCount;
	TF* arrNorm;
};

double getTFValue(TF_list List, int i);

void TFListInit(TF_list&);
void addTF(TF_list&, TF);
void LoadTFList(string, TF_list&);
void SaveTFList(string, TF_list);
void FreeTFList(TF_list&);

void TFList_Input(TF_list&, string*, int);