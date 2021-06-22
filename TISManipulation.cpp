#pragma warning(disable:4996)
#include "TISManipulation.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>

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

void TFList_Input(TF_list& List, string* data, int n) // data is sorted increasingly
{
	int count = 0;
	for (int i = 0; i < n - 1; i++)
	{
		count++;
		if (data[i] != data[i + 1]) {
			TF t{ "\0", count };
			strcpy(t.word, data[i].c_str());
			addTF(List, t);
			count = 0;
		}
	}
	if (count > 0)
	{
		TF t{ "\0", count };
		strcpy(t.word, data[n - 1].c_str());
		addTF(List, t);
		count = 0;
	}
}