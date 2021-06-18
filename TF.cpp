#include "TF.h"

#pragma warning(disable:4996)

void TFListInit(TF_list &List)
{
	List.size = 0;
	List.totalCount = 0;
	List.capacity = 100;
	List.arrNorm = new TF[100];
	List.arrTele = new TF[100];
}

void addTF(TF_list &List, TF data, bool isTelex)
{
	if (List.size == List.capacity) {
		List.capacity += 100;

		TF* temp1 = new TF[List.capacity];
		TF* temp2 = new TF[List.capacity];
		for (int i = 0; i < List.capacity - 100; i++) temp1[i] = List.arrNorm[i];
		for (int i = 0; i < List.capacity - 100; i++) temp2[i] = List.arrTele[i];
		delete[] List.arrNorm;
		delete[] List.arrTele;
		List.arrNorm = temp1;
		List.arrTele = temp2;
	}

	List.totalCount += data.count;

	if (isTelex)
		List.arrTele[List.size++] = data;
	else
		List.arrNorm[List.size++] = data;
}

void LoadTFList(char *filename, TF_list& List)
{
	FILE* fr = fopen(filename, "rb");
	if (!fr) {
		fprintf(stderr, "Cannot read TF list!\n");
		return;
	}

	FreeTFList(List);
	fread(&List.capacity, sizeof(int), 1, fr);
	fread(&List.size, sizeof(int), 1, fr);
	fread(&List.totalCount, sizeof(int), 1, fr);
	fread(List.arrNorm, sizeof(TF), List.capacity, fr);
	fread(List.arrTele, sizeof(TF), List.capacity, fr);

	fclose(fr);
}

void SaveTFList(char *filename, TF_list List)
{
	FILE* fw = fopen(filename, "wb");
	if (!fw) {
		fprintf(stderr, "Cannot save TF list!\n");
		return;
	}


	fwrite(&List.capacity, sizeof(int), 1, fw);
	fwrite(&List.size, sizeof(int), 1, fw);
	fwrite(&List.totalCount, sizeof(int), 1, fw);
	fwrite(List.arrNorm, sizeof(TF), List.capacity, fw);
	fwrite(List.arrTele, sizeof(TF), List.capacity, fw);

	fclose(fw);
}

void FreeTFList(TF_list &List)
{
	delete[] List.arrNorm;
	delete[] List.arrTele;
	List.arrNorm = nullptr;
	List.arrTele = nullptr;
	List.totalCount = 0;
	List.capacity = 0;
	List.size = 0;
}
