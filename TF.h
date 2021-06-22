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

void TFListInit(TF_list&);
void addTF(TF_list&, TF);
void LoadTFList(char*, TF_list&);
void SaveTFList(char*, TF_list);
void FreeTFList(TF_list&);