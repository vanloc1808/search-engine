#include "TF.h"
#include <fstream>
using namespace std;
#pragma warning(disable:4996)

void TFListInit(TF_list &List)
{
	List.size = 0;
	List.totalCount = 0;
	List.capacity = 100;
	List.arrNorm = new TF[100];
}

void addTF(TF_list &List, TF data)
{
	if (List.size == List.capacity) {
		List.capacity += 100;

		TF* temp1 = new TF[List.capacity];
		for (int i = 0; i < List.capacity - 100; i++) temp1[i] = List.arrNorm[i];
		delete[] List.arrNorm;
		List.arrNorm = temp1;
	}

	List.totalCount += data.count;
	List.arrNorm[List.size++] = data;
}

void LoadTFList(char *filename, TF_list& List)
{
	ifstream fr(filename, ios::in | ios::binary);

	fr.read((char*)&List.size, sizeof(int));
	fr.read((char*)&List.totalCount, sizeof(int));
	fr.read((char*)&List.arrNorm, sizeof(TF) * List.size);

	/*FreeTFList(List);
	
	fr >> List.capacity >> List.size >> List.totalCount;
	fr.ignore();

	string s = "";

	List.arrNorm = new TF[List.capacity];

	for (int i = 0; i < List.size; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].count = stoi(s);
	}*/

	fr.close();
}

void SaveTFList(char *filename, TF_list List)
{
	ofstream fw(filename, ios::out | ios::binary);

	fw.write((char*)&List.size, sizeof(int));
	fw.write((char*)&List.totalCount, sizeof(int));
	fw.write((char*)&List.arrNorm, sizeof(TF) * List.size);

	/*fw << List.size << "\n" << List.size << "\n" << List.totalCount << "\n";
	for (int i = 0; i < List.capacity; i++)
	{
		fw << List.arrNorm[i].word << "\n";
		fw << List.arrNorm[i].count << "\n";
	}*/

	fw.close();
}

void FreeTFList(TF_list &List)
{
	delete[] List.arrNorm;
	List.arrNorm = nullptr;
	List.totalCount = 0;
	List.capacity = 0;
	List.size = 0;
}
