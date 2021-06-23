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

int bSearch_TF(TF_list List, string key) // Find how many word in document
{
	int l = 0;
	int h = List.size - 1;
	while (l <= h) {
		int m = (l + h) / 2;
		if (key == List.arrNorm[m].word)
			return List.arrNorm[m].count;
		if (key < List.arrNorm[m].word) {
			h = m - 1;
		} else {
			l = m + 1;
		}
	}
	return 0;
}

void TFList_Input(TF_list& List, string* data, int n) // data is sorted increasingly
{
	int count = 0;
	for (int i = 0; i < n - 1; i++)
	{
		count++;
		if (data[i] != data[i + 1]) {
			TF t{ data[i], count };
			addTF(List, t);
			count = 0;
		}
	}
	if (count > 0)
	{
		TF t{ data[n - 1], count };
		addTF(List, t);
		count = 0;
	}
}