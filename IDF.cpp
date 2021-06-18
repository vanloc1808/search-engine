#include "IDF.h"
#include <stdio.h>
#include <memory.h>

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
	FILE* fr = fopen(filename, "rb");
	if (!fr) {
		fprintf(stderr, "Cannot read IDF list!\n");
		return;
	}

	FreeIDFList(List);
	fread(&List.capacity, sizeof(int), 1, fr);
	fread(&List.size, sizeof(int), 1, fr);
	fread(List.arrNorm, sizeof(IDF), List.capacity, fr);
	fread(List.arrTele, sizeof(IDF), List.capacity, fr);

	fclose(fr);
}

void SaveIDFList(char *filename, IDF_list List)
{
	FILE* fw = fopen(filename, "wb");
	if (!fw) {
		fprintf(stderr, "Cannot save IDF list!\n");
		return;
	}

	fwrite(&List.capacity, sizeof(int), 1, fw);
	fwrite(&List.size, sizeof(int), 1, fw);
	fwrite(List.arrNorm, sizeof(IDF), List.capacity, fw);
	fwrite(List.arrTele, sizeof(IDF), List.capacity, fw);

	fclose(fw);
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
