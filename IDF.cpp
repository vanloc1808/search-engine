#include "IDF.h"
#include <stdio.h>
#include <memory.h>
#include <fstream>
using namespace std;

#pragma warning(disable:4996)

void IDFListInit(IDF_list &List)
{
	List.size = 0;	
	List.capacity = 100;
	List.arrNorm = new IDF[100];
	List.arrTele = new IDF[100];
}

void addIDF(IDF_list &List, IDF data, bool isTelex)
{
	if (List.size == List.capacity) {
		List.capacity += 100;

		IDF* temp1 = new IDF[List.capacity];
		IDF* temp2 = new IDF[List.capacity];
		for (int i = 0; i < List.capacity - 100; i++) temp1[i] = List.arrNorm[i];
		for (int i = 0; i < List.capacity - 100; i++) temp2[i] = List.arrTele[i];
		delete[] List.arrNorm;
		delete[] List.arrTele;
		List.arrNorm = temp1;
		List.arrTele = temp2;
	}

	if (isTelex)
		List.arrTele[List.size++] = data;
	else
		List.arrNorm[List.size++] = data;
}

void LoadIDFList(char *filename, IDF_list &List)
{
	ifstream fr(filename, ios::in);

	FreeIDFList(List);

	fr >> List.capacity >> List.size;
	string s = "";
	fr.ignore();
	List.arrNorm = new IDF[List.capacity];
	List.arrTele = new IDF[List.capacity];

	for (int i = 0; i < List.capacity; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].value = stod(s);
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].name = s;
	}

	for (int i = 0; i < List.capacity; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrTele[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrTele[i].value = stod(s);
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrTele[i].name = s;
	}

	fr.close();
}

void SaveIDFList(char *filename, IDF_list List)
{
	ofstream fw(filename, ios::out);

	fw << List.capacity << "\n";
	fw << List.size << "\n";
	for (int i = 0; i < List.capacity; i++)
	{
		fw << List.arrNorm[i].word << "\n";
		fw << List.arrNorm[i].value << "\n";
		fw << List.arrNorm[i].name << "\n";
	}
	for (int i = 0; i < List.capacity; i++)
	{
		fw << List.arrTele[i].word << "\n";
		fw << List.arrTele[i].value << "\n";
		fw << List.arrTele[i].name << "\n";
	}

	fw.close();
}

void FreeIDFList(IDF_list &List)
{
	delete[] List.arrNorm;
	delete[] List.arrTele;
	List.arrNorm = nullptr;
	List.arrTele = nullptr;
	List.capacity = 0;
	List.size = 0;
}
