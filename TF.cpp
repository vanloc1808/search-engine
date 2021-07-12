#include "TF.h"
#include <fstream>
using namespace std;

double getTFValue(const TF_list List, const int i)
{
	if(i >= List.size)
		return 0;
	return 0.5 + 0.5 * (static_cast<double>(List.arrNorm[i].count) / List.maxCount);
}

void tfListInit(TF_list &List)
{
	List.size = 0;
	List.maxCount = 0;
	List.capacity = 1000;
	List.arrNorm = new TF[1000];
}

void addTF(TF_list &List, const TF& Data)
{
	if (List.size == List.capacity) {
		List.capacity += 1000;

		TF* temp1 = new TF[List.capacity];
		TF* temp2 = new TF[List.capacity];
		for (int i = 0; i < List.capacity - 1000; i++) temp1[i] = List.arrNorm[i];
		delete[] List.arrNorm;
		List.arrNorm = temp1;
	}

	List.maxCount = (List.maxCount < Data.count) ? Data.count : List.maxCount;
	List.arrNorm[List.size++] = Data;
}

void loadTFList(const string& Filename, TF_list& List)
{
	ifstream fr(Filename, ios::in);

	//freeTFList(List);
	
	fr >> List.capacity >> List.size >> List.maxCount;
	fr.ignore();

	string s;

	List.arrNorm = new TF[List.capacity];

	for (int i = 0; i < List.size; i++)
	{
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].word = s;
		getline(fr, s);
		if (s.length() > 0 && s.back() == '\r') s.pop_back();
		List.arrNorm[i].count = stoi(s);
	}

	fr.close();
}

void saveTFList(const string& Filename, const TF_list List)
{
	ofstream fw(Filename, ios::out);

	fw << List.size << "\n" << List.size << "\n" << List.maxCount << "\n";
	for (int i = 0; i < List.size; i++)
	{
		fw << List.arrNorm[i].word << "\n";
		fw << List.arrNorm[i].count << "\n";
	}

	fw.close();
}

void freeTFList(TF_list &List)
{
	delete[] List.arrNorm;
	List.arrNorm = nullptr;
	List.maxCount = 0;
	List.capacity = 0;
	List.size = 0;
}

void tfListInput(TF_list& List, string* Data, const int N) // Supposed data is sorted increasingly
{
	int count = 0;
	for (int i = 0; i < N - 1; i++)
	{
		count++;
		if (Data[i] != Data[i + 1]) {
			TF t{ Data[i], count };
			addTF(List, t);
			count = 0;
		}
	}
	if (count > 0)
	{
		const TF t{ Data[N - 1], count };
		addTF(List, t);
		count = 0;
	}
}