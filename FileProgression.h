#pragma once

#include <iostream>
#include "TF.h"
#include "IDF.h"
using namespace std;

void updateMetadata(string path);
void createMetadata(string folderDataset);
void prepareFile(string folderPath);
IDF_list createIDF(string folderPath);
void loadToRAM();
void freeRAM();
void searchSentence(string sentence);