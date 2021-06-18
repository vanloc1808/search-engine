#include <string>
using std::string;

struct TF {
    string word;
    double val;
    int count;
};

struct TF_list {
	int size;
	int capacity;
	TF* arrNorm;
	TF* arrTele;
};

void TFListInit(TF_list&);
void addTF(TF_list&, TF, bool);
void LoadTFList(char*, TF_list&);
void SaveTFList(char*, TF_list);
void FreeTFList(TF_list&);