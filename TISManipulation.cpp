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
