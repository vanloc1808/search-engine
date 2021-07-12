#include "IDF.h"
#include <cstdio>
#include <memory.h>
#include <cmath>
#include <fstream>
#include <utility>
using namespace std;

double getIDFValue(const IDF_list List, const int i)
{
	if(i >= List.size)
		return 0;
	return log10(static_cast<double>(List.numFile) / List.arrNorm[i].value);
}

void idfListInit(IDF_list &List)
{
	List.size = 0;	
	List.numFile = 0;
	List.capacity = 1000;
	List.arrNorm = new IDF[1000];
}

void addIDF(IDF_list &List, IDF Data)
{
	if (List.size == List.capacity) {
		List.capacity += 1000;

		IDF* temp1 = new IDF[List.capacity];
		IDF* temp2 = new IDF[List.capacity];
		for (int i = 0; i < List.capacity - 1000; i++) temp1[i] = List.arrNorm[i];
		delete[] List.arrNorm;
		List.arrNorm = temp1;
	}
	List.arrNorm[List.size++] = std::move(Data);
}

void loadIDFList(const string& Filename, IDF_list &List)
{
	ifstream fr(Filename, ios::in);

	//freeIDFList(List);

	fr >> List.capacity >> List.size >> List.numFile;
	string s;
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

void saveIDFList(const string& Filename, const IDF_list List)
{
	ofstream fw(Filename, ios::out);

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

void freeIDFList(IDF_list &List)
{
	delete[] List.arrNorm;
	List.arrNorm = nullptr;
	List.capacity = 0;
	List.size = 0;
	List.numFile = 0;
}

void idfListInput(IDF_list& List, const int NumFile, string* Data, const int N) // Supposed data is sorted increasingly
{
	List.numFile = NumFile;
	int count = 0;
	for (int i = 0; i < N - 1; i++)
	{
		count++;
		if (Data[i] != Data[i + 1]) {
			if (count >= NumFile) // idf = 0
			{
				count = 0;
				continue;
			}
			const IDF idf{ Data[i], count };
			addIDF(List, idf);
			count = 0;
		}
	}
	if (count > 0 && count < NumFile)
	{
		const IDF idf{ Data[N - 1], count };
		addIDF(List, idf);
		count = 0;
	}
}
