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

int bSearch_TF(TF_list List, string key) // Find how many word in document
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