#include "TF.h"

void TFListInit(TF_list &List)
{
	List.size = 0;
	List.totalCount = 0;
	List.capacity = 100;
	List.arrNorm = (TF*)malloc(100 * sizeof(TF));
	List.arrTele = (TF*)malloc(100 * sizeof(TF));
}

void addTF(TF_list &List, TF data, bool isTelex)
{
	if (List.size == List.capacity) {
		List.capacity += 100;
		List.arrNorm = (TF*)realloc(List.arrNorm, List.capacity * sizeof(TF));
		List.arrTele = (TF*)realloc(List.arrTele, List.capacity * sizeof(TF));
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
	free(List.arrNorm);
	free(List.arrTele);
	List.arrNorm = nullptr;
	List.arrTele = nullptr;
	List.totalCount = 0;
	List.capacity = 0;
	List.size = 0;
}
