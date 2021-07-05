#pragma once

#include <iostream>
#include "TF.h"
#include "IDF.h"
using namespace std;

void getSubFolderDirectory(string folder);
void createMetadata(string folderDataset);
IDF_list createIDF(string folderPath);
void getSubFolderName(string folder/*, string*& subFolderName, int& idx*/);

void getFileDirectory(string folder/*, string* subFolderName, int idx*/);

void fileDirecProgression(string folder/*, string*& subFolderName*/);

void IterateFile(std::string &directory, std::wstring &s, unsigned int &size, unsigned int &capacity, std::string * &strArr);

void fileInput();