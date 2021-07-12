#include "Utility.h"
#include <fstream>
#include <thread>
#include <utility>
#include "IDF.h"
using namespace std;

const int BLOCK = 1000;
const int INIT_SIZE = 10000;

const string TEMP = getenv("TEMP");

const char SEPARATOR = '\\';

void initString(StringArray &Sa)
{
	Sa.cap = INIT_SIZE;
	Sa.size = 0;
	Sa.array = new string[Sa.cap];
}

void addString(StringArray &Sa, string s)
{
	if (Sa.size == Sa.cap) {
		Sa.cap += BLOCK;

		string* temp = new string[Sa.cap];
		for (int i = 0; i < Sa.size; i++)
			temp[i] = Sa.array[i];

		delete[] Sa.array;
		Sa.array = temp;
	}
	Sa.array[Sa.size++] = std::move(s);
}

void deleteArray(StringArray &Sa)
{
	delete[] Sa.array;
	Sa.cap = 0;
	Sa.size = 0;
}

void loadTextToArray(StringArray &Sa, const string& Filename)
{
	ifstream fin(Filename, ios::in);
	Sa.size = 0;
	string temp;
	while(getline(fin, temp)) 
	{
		addString(Sa, temp);
	}
	fin.close();
}

// ------------------------------------

void makeFolderWrapper(const string& PathToFolder)
{
	evalCommand(string("mkdir \"") + PathToFolder + "\">nul");
}

void getFolderWrapper(const string& PathToFolder, const string& PathToOutputFile)
{
	evalCommand(string("dir \"") + PathToFolder + string("\" /s /b /o:n /ad > %TEMP%\\folder_temp.txt"));

	ifstream input(TEMP + "\\folder_temp.txt", ios::in);
	ofstream output(PathToOutputFile, ios::out);

	string temp;
	while (getline(input, temp)) {
		output << extractPath(temp) << "\n";
	}

	input.close();
	output.close();
	deleteFileWrapper("%TEMP%\\folder_temp.txt");
}

void getFileWrapper(const string& PathToFolder, const string& PathToOutputFile)
{
	
	evalCommand(string("dir \"") + PathToFolder + string("\" /s /b /o:n > %TEMP%\\file_temp.txt"));
	ifstream input(TEMP + "\\file_temp.txt", ios::in);
	ofstream output(PathToOutputFile, ios::out);

	string temp;
	while (getline(input, temp)) {
		output << extractPath(temp) << "\n";
	}

	input.close();
	output.close();
	deleteFileWrapper("%TEMP%\\file_temp.txt");
}

void deleteFileWrapper(const string& PathToFile)
{
	evalCommand(string("del /q \"") + PathToFile + string("\""));
}

string extractPath(string Path)
{
	int i = Path.length() - 1;
	while (i >= 0 && Path[i] != SEPARATOR) i--;
	return Path.substr(i + 1);
}

void copyFolderWrapper(const string& PathToFolder, const string& PathToOutput)
{
	evalCommand(string("xcopy /E/I/Y \"") + PathToFolder + "\" \"" + PathToOutput + "\" >nul");
}

void openFileWithNotepadWrapper(const string& PathToFile)
{
	evalCommand(string("notepad ") + PathToFile);
}

// ---------------------------------



void evalCommand(const string& Command)
{
	system(Command.c_str());
}

string* mergeArray(string* A, const int Na, string* B, const int Nb)
{
	int i = 0;
	int j = 0;
	int k = 0;
	string* res = new string[Na + Nb];
	while ((i < Na) && (j < Nb)) {
		if (A[i] < B[j])
			res[k++] = A[i++];
		else
			res[k++] = B[j++];
	}
	while (i < Na)
		res[k++] = A[i++];
	while (j < Nb)
		res[k++] = B[j++];
	return res;
}

void sortString(string *Arr, const int N)
{
	if (N == 1)
		return;
	const int m = N / 2;

	sortString(Arr, m);
	sortString(Arr + m, N - m);

	string* temp = mergeArray(Arr, m, Arr + m, N - m);
	for (int i = 0; i < N; i++) Arr[i] = temp[i];
	delete[] temp;
}

void sortMultiThread(StringArray &Sa)
{
	const int n = Sa.size;
	int m = n / 2;
	thread t1(sortString, Sa.array, m);
	thread t2(sortString, Sa.array + m, n - m);
	t1.join();
	t2.join();
	string* temp = mergeArray(Sa.array, m, Sa.array + m, n - m);
	for (int i = 0; i < n; i++) Sa.array[i] = temp[i];
	delete[] temp;
}

int bSearchTF(const TF_list List, const string& Key) 
{
	int l = 0;
	int h = List.size - 1;
	while (l <= h) {
		const int m = (l + h) / 2;
		if (Key == List.arrNorm[m].word)
			return m;
		if (Key < List.arrNorm[m].word) 
			h = m - 1;
		else 
			l = m + 1;
	}
	return -1;
}

int bSearchIDF(const IDF_list List, const string& Key) 
{
	int l = 0;
	int h = List.size - 1;
	while (l <= h) {
		const int m = (l + h) / 2;
		if (Key == List.arrNorm[m].word)
			return m;
		if (Key < List.arrNorm[m].word) 
			h = m - 1;
		else 
			l = m + 1;
	}
	return -1;
}

// ----------------------------------

void initResponse(ResponseData &Rd)
{
	Rd.cap = INIT_SIZE;
	Rd.size = 0;
	Rd.file = new FileData[Rd.cap];
}

void addResponse(ResponseData &Rd, const FileData F)
{
	if (Rd.size == Rd.cap) {
		Rd.cap += BLOCK;

		FileData* temp = new FileData[Rd.cap];
		for (int i = 0; i < Rd.size; i++)
			temp[i] = Rd.file[i];

		delete[] Rd.file;
		Rd.file = temp;
	}
	Rd.file[Rd.size++] = F;
}

void deleteResponse(ResponseData &Rd)
{
	delete[] Rd.file;
	Rd.cap = 0;
	Rd.size = 0;
}

void intersectResponse(ResponseData &Dest, const ResponseData Sour)
{
	for(int i = 0; i < Sour.size; i++)
	{
		for(int j = 0; j < Dest.size; j++)
		{
			if(Dest.file[j].posFolder == Sour.file[i].posFolder && Dest.file[j].posFile == Sour.file[i].posFile)
				Dest.file[j].intersectionCount++;
		}
	}
}

void swap(FileData &A, FileData &B) noexcept
{
	const FileData t = A;
	A = B;
	B = t;
}

bool cmp(const FileData A, const FileData B)
{
	if(A.intersectionCount > B.intersectionCount)
		return true;
	if(A.intersectionCount == B.intersectionCount)
	{
		return A.value > B.value;
	}
	return false;
}

int partition(FileData* Arr, const int L, const int R)
{
	int i = L;
	const FileData pivot = Arr[R];
	for(int j = L; j < R; j++) {
		if(cmp(Arr[j], pivot))
		{
			swap(Arr[j], Arr[i]);
			i++;
		}
	}
	swap(Arr[i], Arr[R]);
	return i;
}

void quickSort(FileData* Arr, const int L, const int R)
{
	if(L < R)
	{
		const int p = partition(Arr, L, R);
		quickSort(Arr, L, p - 1);
		quickSort(Arr, p + 1, R);
	}
}

void sortResponse(ResponseData &Rd)
{
	quickSort(Rd.file, 0, Rd.size - 1);
}