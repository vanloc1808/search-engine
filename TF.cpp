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
	List.arrTele = new TF[100];
}

void addTF(TF_list &List, TF data, bool isTelex)
{
	if (List.size == List.capacity) {
		List.capacity += 100;

		TF* temp1 = new TF[List.capacity];
		TF* temp2 = new TF[List.capacity];
		for (int i = 0; i < List.capacity - 100; i++) temp1[i] = List.arrNorm[i];
		for (int i = 0; i < List.capacity - 100; i++) temp2[i] = List.arrTele[i];
		delete[] List.arrNorm;
		delete[] List.arrTele;
		List.arrNorm = temp1;
		List.arrTele = temp2;
	}

	List.totalCount += data.count;

	if (isTelex)
		List.arrTele[List.size++] = data;
	else
		List.arrNorm[List.size++] = data;
}

void LoadTFList(char *filename, TF_list& List)
{
	ifstream fr(filename, ios::in);

	FreeTFList(List);
	
	fr >> List.capacity >> List.size >> List.totalCount;
	fr.ignore();

	string s = "";
	for (int i = 0; i < List.capacity; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].count = stoi(s);
	}

	for (int i = 0; i < List.capacity; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrTele[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrTele[i].count = stoi(s);
	}

	fr.close();
}

void SaveTFList(char *filename, TF_list List)
{
	ofstream fw(filename, ios::out);

	fw << List.capacity << "\n" << List.size << "\n" << List.totalCount << "\n";
	for (int i = 0; i < List.capacity; i++)
	{
		fw << List.arrNorm[i].word << "\n";
		fw << List.arrNorm[i].count << "\n";
	}

	for (int i = 0; i < List.capacity; i++)
	{
		fw << List.arrTele[i].word << "\n";
		fw << List.arrTele[i].count << "\n";
	}

	fw.close();
}

void FreeTFList(TF_list &List)
{
	delete[] List.arrNorm;
	delete[] List.arrTele;
	List.arrNorm = nullptr;
	List.arrTele = nullptr;
	List.totalCount = 0;
	List.capacity = 0;
	List.size = 0;
}
