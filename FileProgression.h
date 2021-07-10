#pragma once

#include <iostream>
#include "TF.h"
#include "IDF.h"
using namespace std;


void createMetadata(string folderDataset);
void prepareFile(string folderPath);
IDF_list createIDF(string folderPath);
void loadToRAM();
void searchSentence(string sentence);