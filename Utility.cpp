#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"
#include <fstream>
#include <thread>
#include "IDF.h"
using namespace std;

const int BLOCK = 1000;
const int INIT_SIZE = 10000;

const string TEMP = getenv("TEMP");

const char SEPARATOR = '\\';

void initString(StringArray &sa)
{
	sa.cap = INIT_SIZE;
	sa.size = 0;
	sa.Array = new string[sa.cap];
}

void addString(StringArray &sa, string s)
{
	if (sa.size == sa.cap) {
		sa.cap += BLOCK;

		string* temp = new string[sa.cap];
		for (int i = 0; i < sa.size; i++)
			temp[i] = sa.Array[i];

		delete[] sa.Array;
		sa.Array = temp;
	}
	sa.Array[sa.size++] = s;
}

void deleteArray(StringArray &sa)
{
	delete[] sa.Array;
	sa.cap = 0;
	sa.size = 0;
}

void loadTextToArray(StringArray &sa, string filename)
{
	ifstream fin(filename, ios::in);
	sa.size = 0;
	string temp = "";
	while(getline(fin, temp)) 
	{
		addString(sa, temp);
	}
	fin.close();
}

// ------------------------------------

void makeFolderWrapper(string path_to_folder)
{
	evalCommand(string("mkdir \"") + path_to_folder + "\"");
}

void getFolderWrapper(string path_to_folder, string path_to_outputFile)
{
	evalCommand(string("dir \"") + path_to_folder + string("\" /s /b /o:n /ad > %TEMP%\\folder_temp.txt"));

	ifstream input(TEMP + "\\folder_temp.txt", ios::in);
	ofstream output(path_to_outputFile, ios::out);

	string temp = "";
	while (getline(input, temp)) {
		output << extractPath(temp) << "\n";
	}

	input.close();
	output.close();
	deleteFileWrapper("%TEMP%\\folder_temp.txt");
}

void getFileWrapper(string path_to_folder, string path_to_outputFile)
{
	
	evalCommand(string("dir \"") + path_to_folder + string("\" /s /b /o:n > %TEMP%\\file_temp.txt"));
	ifstream input(TEMP + "\\file_temp.txt", ios::in);
	ofstream output(path_to_outputFile, ios::out);

	string temp = "";
	while (getline(input, temp)) {
		output << extractPath(temp) << "\n";
	}

	input.close();
	output.close();
	deleteFileWrapper("%TEMP%\\file_temp.txt");
}

void deleteFileWrapper(string path_to_file)
{
	evalCommand(string("del /q \"") + path_to_file + string("\""));
}

string extractPath(string path)
{
	int i = path.length() - 1;
	while (i >= 0 && path[i] != SEPARATOR) i--;
	return path.substr(i + 1);
}

// ---------------------------------



void evalCommand(string command)
{
	system(command.c_str());
}

string* mergeArray(string* A, int nA, string* B, int nB)
{
	int i = 0;
	int j = 0;
	int k = 0;
	string* res = new string[nA + nB];
	while ((i < nA) && (j < nB)) {
		if (A[i] < B[j])
			res[k++] = A[i++];
		else
			res[k++] = B[j++];
	}
	while (i < nA)
		res[k++] = A[i++];
	while (j < nB)
		res[k++] = B[j++];
	return res;
}

void sort_String(string *arr, int n)
{
	if (n == 1)
		return;
	int m = n / 2;

	sort_String(arr, m);
	sort_String(arr + m, n - m);

	string* temp = mergeArray(arr, m, arr + m, n - m);
	for (int i = 0; i < n; i++) arr[i] = temp[i];
	delete[] temp;
}

void sort_multiThread(StringArray &sa)
{
	int n = sa.size;
	int m = n / 2;
	thread t1(sort_String, sa.Array, m);
	thread t2(sort_String, sa.Array + m, n - m);
	t1.join();
	t2.join();
	string* temp = mergeArray(sa.Array, m, sa.Array + m, n - m);
	for (int i = 0; i < n; i++) sa.Array[i] = temp[i];
	delete[] temp;
}

int bSearch_TF(TF_list List, string key) 
{
	int l = 0;
	int h = List.size - 1;
	while (l <= h) {
		int m = (l + h) / 2;
		if (key == List.arrNorm[m].word)
			return m;
		if (key < List.arrNorm[m].word) {
			h = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return -1;
}

int bSearch_IDF(IDF_list List, string key) 
{
	int l = 0;
	int h = List.size - 1;
	while (l <= h) {
		int m = (l + h) / 2;
		if (key == List.arrNorm[m].word)
			return m;
		if (key < List.arrNorm[m].word) {
			h = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return -1;
}

// ----------------------------------

void initResponse(ResponseData &rd)
{
	rd.cap = INIT_SIZE;
	rd.size = 0;
	rd.file = new fileData[rd.cap];
}

void addResponse(ResponseData &rd, fileData f)
{
	if (rd.size == rd.cap) {
		rd.cap += BLOCK;

		fileData* temp = new fileData[rd.cap];
		for (int i = 0; i < rd.size; i++)
			temp[i] = rd.file[i];

		delete[] rd.file;
		rd.file = temp;
	}
	rd.file[rd.size++] = f;
}

void deleteResponse(ResponseData &rd)
{
	delete[] rd.file;
	rd.cap = 0;
	rd.size = 0;
}

void intersectResponse(ResponseData &dest, ResponseData sour)
{
	for(int i = 0; i < sour.size; i++)
	{
		for(int j = 0; j < dest.size; j++)
		{
			if(dest.file[j].posFolder == sour.file[i].posFolder && dest.file[j].posFile == sour.file[i].posFile)
				dest.file[j].intersectionCount++;
		}
	}
}

void swap(fileData &a, fileData &b)
{
	fileData t = a;
	a = b;
	b = t;
}

bool cmp(fileData A, fileData B)
{
	if(A.intersectionCount > B.intersectionCount)
		return true;
	if(A.intersectionCount == B.intersectionCount)
	{
		return A.value > B.value;
	}
	return false;
}

int partition(fileData* arr, int l, int r)
{
	int i = l;
	fileData pivot = arr[r];
	for(int j = l; j < r; j++) {
		if(cmp(arr[j], pivot))
		{
			swap(arr[j], arr[i]);
			i++;
		}
	}
	swap(arr[i], arr[r]);
	return i;
}

void quickSort(fileData* arr, int l, int r)
{
	if(l < r)
	{
		int p = partition(arr, l, r);
		quickSort(arr, l, p - 1);
		quickSort(arr, p + 1, r);
	}
}

void sortResponse(ResponseData &rd)
{
	quickSort(rd.file, 0, rd.size - 1);
}