#pragma once
#include <string>
using std::string;

// word | count
struct TF {
    string word;
    int count{};
};

struct TF_list {
	int size;
	int capacity;
	int maxCount;
	TF* arrNorm;
};

double getTFValue(TF_list List, int i);

void tfListInit(TF_list&);
void addTF(TF_list&, const TF&);
void loadTFList(const string&, TF_list&);
void saveTFList(const string&, TF_list);
void freeTFList(TF_list&);

void tfListInput(TF_list&, string*, int);