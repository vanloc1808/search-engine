#include <string>
#include "Normalizer.h"
#include <cctype>
using namespace std;


wchar_t inverse_map[] = { L'a',L'á',L'à',L'ả',L'ã',L'ạ',L'â',L'ấ',L'ầ',L'ẩ',L'ẫ',L'ậ',L'ă',L'ắ',L'ằ',L'ẳ',L'ẵ',L'ặ', \
  L'e',L'ê',L'ế',L'ề',L'ể',L'ễ', L'ệ', L'é', L'è', L'ẻ', L'ẽ', L'ẹ', \
  L'i',L'í',L'ì',L'ỉ',L'ĩ', L'ị', \
  L'o',L'ó',L'ò',L'ỏ',L'õ', L'ọ', L'ô', L'ố', L'ồ', L'ổ', L'ỗ', L'ộ', L'ớ', L'ờ', L'ở', L'ỡ', L'ợ', L'ơ', \
  L'u',L'ú',L'ù',L'ủ',L'ũ', L'ụ', L'ư', L'ứ', L'ừ', L'ử', L'ự', L'ữ', \
  L'b',L'c',L'đ',L'd',L'f',L'g',L'h',L'j',L'k',L'l',L'm',L'n',L'p',L'q',L'r',L's',L't',L'v',L'w',L'x',L'y',L'ý',L'ỳ',L'ỷ',L'ỹ',L'ỵ',L'z'};

//string telexMap[] = { "a","as","af","ar","ax","aj","aa","aas","aaf","aar","aax","aaj","aw","aws","awf","awr","awx","awj", \
//  "e","ee","ees","eef","eer","eex","eej","es","ef","er","ex","ej", \
//  "i","is","if","ir","ix","ij", \
//  "o","os","of","or","ox","oj","oo","oos","oof","oor","oox","ooj","ows","owf","owr","owx","owj","ow", \
//  "u","us","uf","ur","ux","uj","uw","uws","uwf","uwr","uwj","uwx", \
//  "b","c","dd","d","f","g","h","j","k","l","m","n","p","q","r","s","t","v","w","x","y","ys","yf","yr","yx","yj","z" };

wchar_t inverse_capital_map[] = { L'A',L'Á',L'À',L'Ả',L'Ã',L'Ạ',L'Â',L'Ấ',L'Ầ',L'Ẩ',L'Ẫ',L'Ậ',L'Ă',L'Ắ',L'Ằ',L'Ẳ',L'Ẵ',L'Ặ', \
  L'E',L'Ê',L'Ế',L'Ề',L'Ể',L'Ễ', L'Ệ', L'É', L'È', L'Ẻ', L'Ẽ', L'Ẹ', \
  L'I',L'Í',L'Ì',L'Ỉ',L'Ĩ', L'Ị', \
  L'O',L'Ó',L'Ò',L'Ỏ',L'Õ', L'Ọ', L'Ô', L'Ố', L'Ồ', L'Ổ', L'Ỗ', L'Ộ', L'Ớ', L'Ờ', L'Ở', L'Ỡ', L'Ợ', L'Ơ', \
  L'U',L'Ú',L'Ù',L'Ủ',L'Ũ', L'Ụ', L'Ư', L'Ứ', L'Ừ', L'Ử', L'Ự', L'Ữ', \
  L'B',L'C',L'Đ',L'D',L'F',L'G',L'H',L'J',L'K',L'L',L'M',L'N',L'P',L'Q',L'R',L'S',L'T',L'V',L'W',L'X',L'Y',L'Ý',L'Ỳ',L'Ỷ',L'Ỹ',L'Ỵ',L'Z' };

char normal_map[] = { 'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a', \
  'e','e','e','e','e','e','e','e','e','e','e','e', \
  'i','i','i','i','i','i', \
  'o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o', \
  'u','u','u','u','u','u','u','u','u','u','u','u', \
  'b','c','d','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','y','y','y','y','y','z' };


// Keeps only latin word & number from vietnamese word
string VEconvert(const wstring& Source) { 
  string result;
  for (wchar_t t : Source)
  {
    int pos = 0;
    for (; pos < 93 && t != inverse_map[pos] && t != inverse_capital_map[pos]; pos++){}
	if ((pos == 93) && !((48 <= t) && (t <= 57))) {
		continue;
	}
    result += normal_map[pos];
  }
  return result;
}

// Return removed punctuation string
string normalPunctuation(const string& S) {
	string temp;
	for (char i : S)
	{
		if (!ispunct(i)) {
			temp += i;
		}
	}
	return temp;
}

