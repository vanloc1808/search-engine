#pragma once
#include <iostream>
using std::string;

bool isFirstTime();
void updateMetadata(string Path);
void createMetadata(const string& folderDataset);
void prepareFile(const string& FolderPath);
void loadToRAM();
void freeRAM();
void searchSentence(const string& Sentence);