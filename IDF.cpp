#include "IDF.h"
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <fstream>
using namespace std;

#pragma warning(disable:4996)

double getIDFValue(IDF_list List, int i)
{
	if(i >= List.size)
		return 0;
	return log10((double)List.numFile / List.arrNorm[i].value);
}

void IDFListInit(IDF_list &List)
{
	List.size = 0;	
	List.numFile = 0;
	List.capacity = 1000;
	List.arrNorm = new IDF[1000];
}

void addIDF(IDF_list &List, IDF data)
{
	if (List.size == List.capacity) {
		List.capacity += 1000;

		IDF* temp1 = new IDF[List.capacity];
		IDF* temp2 = new IDF[List.capacity];
		for (int i = 0; i < List.capacity - 1000; i++) temp1[i] = List.arrNorm[i];
		delete[] List.arrNorm;
		List.arrNorm = temp1;
	}
	List.arrNorm[List.size++] = data;
}

void LoadIDFList(string filename, IDF_list &List)
{
	ifstream fr(filename, ios::in);

	//FreeIDFList(List);

	fr >> List.capacity >> List.size >> List.numFile;
	string s = "";
	fr.ignore();
	List.arrNorm = new IDF[List.capacity];

	for (int i = 0; i < List.size; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].value = stoi(s);
	}

	fr.close();
}

void SaveIDFList(string filename, IDF_list List)
{
	ofstream fw(filename, ios::out);

	fw << List.size << "\n";
	fw << List.size << "\n";
	fw << List.numFile << "\n";
	for (int i = 0; i < List.size; i++)
	{
		fw << List.arrNorm[i].word << "\n";
		fw << List.arrNorm[i].value << "\n";
	}

	fw.close();
}

void FreeIDFList(IDF_list &List)
{
	delete[] List.arrNorm;
	List.arrNorm = nullptr;
	List.capacity = 0;
	List.size = 0;
	List.numFile = 0;
}

void IDFList_Input(IDF_list& List, int numFile, string* data, int n) // data is sorted increasingly
{
	List.numFile = numFile;
	int count = 0;
	for (int i = 0; i < n - 1; i++)
	{
		count++;
		if (data[i] != data[i + 1]) {
			if (count >= numFile) // idf = 0
			{
				count = 0;
				continue;
			}
			IDF idf{ data[i], count };
			addIDF(List, idf);
			count = 0;
		}
	}
	if (count > 0 && count < numFile)
	{
		IDF idf{ data[n - 1], count };
		addIDF(List, idf);
		count = 0;
	}
}
