#include <string>
#include <iostream>
#include <fstream>
#include <codecvt>
using namespace std;


wchar_t inverseMap[] = {L'a',L'á',L'à',L'ã',L'ạ',L'â',L'ấ',L'ầ',L'ẫ',L'ậ',L'ă',L'ắ',L'ằ',L'ẵ',L'ặ', \
  L'e',L'ê',L'ế',L'ề',L'ễ',L'ệ',L'é',L'è',L'ẽ',L'ẹ', \
  L'i',L'í',L'ì',L'ĩ',L'ị', \
  L'o',L'ó',L'ò',L'õ',L'ọ',L'ô',L'ố',L'ồ',L'ỗ',L'ộ',L'ớ',L'ờ',L'ỡ',L'ợ',L'ơ', \
  L'u',L'ú',L'ù',L'ũ',L'ụ',L'ư',L'ứ',L'ừ',L'ự',L'ữ', \
  L'b',L'c',L'đ',L'd',L'f',L'g',L'h',L'j',L'k',L'l',L'm',L'n',L'p',L'q',L'r',L's',L't',L'v',L'w',L'x',L'y',L'z'};

char normalMap[] = {'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a', \
  'e','e','e','e','e','e','e','e','e','e', \
  'i','i','i','i','i', \
  'o','o','o','o','o','o','o','o','o','o','o','o','o','o','o', \
  'u','u','u','u','u','u','u','u','u','u', \
  'b','c','d','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};

char telexMap[] = { 'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a', \
  'e','e','e','e','e','e','e','e','e','e', \
  'i','i','i','i','i', \
  'o','o','o','o','o','o','o','o','o','o','o','o','o','o','o', \
  'u','u','u','u','u','u','u','u','u','u', \
  'b','c','d','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z' }; // UnderConstruction

string VEconvert(wstring source) {
  string result = "";
  for(unsigned int i = 0; i < source.length(); i++) {
    int pos = 0;
	wchar_t t = source[i];
	for (; pos < 77 && t != inverseMap[pos]; pos++);
	if (pos == 77) {
		result += t;
		continue;
	}
    result += normalMap[pos];
  }
  return result;
}

#pragma warning(disable:4996)

int main()
{
	wifstream fin("input.txt");
	fin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wstring s;
	getline(fin, s);

	cout << VEconvert(s) << endl;

	fin.close();

    return 0;
}
