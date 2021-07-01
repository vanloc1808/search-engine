#pragma once
#include <string>
#include "TF.h"
#include "IDF.h"
using std::string;
void sort_String(string*, int n); // Increasingly!
int bSearch_TF(TF_list, string);
void TFList_Input(TF_list& List, string* data, int n);
void sort_multiThread(string* arr, int n);