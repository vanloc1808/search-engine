#include "IDF.h"
#include <stdio.h>
#include <memory.h>

void IDFListInit(IDF_list &List)
{
	List.size = 0;	
	List.capacity = 100;
	List.arrNorm = (IDF*)malloc(100 * sizeof(IDF));
	List.arrTele = (IDF*)malloc(100 * sizeof(IDF));
}

void addIDF(IDF_list &List, IDF data, bool isTelex)
{
	if (List.size == List.capacity) {
		List.capacity += 100;
		List.arrNorm = (IDF*)realloc(List.arrNorm, List.capacity * sizeof(IDF));
		List.arrTele = (IDF*)realloc(List.arrTele, List.capacity * sizeof(IDF));
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
	free(List.arrNorm);
	free(List.arrTele);
	List.arrNorm = nullptr;
	List.arrTele = nullptr;
	List.capacity = 0;
	List.size = 0;
}
