/*
ID: silxikys
PROG: cryptcow
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

ofstream fout("cryptcow.out");
ifstream fin("cryptcow.in");

const string message = "Begin the Escape execution at the Break of Dawn";
const char encrypts[] = {'C','O','W'};
int letterCount[128];
bool ans;
int ansDepth = 0;
bool isEncrypt(char c) 
{
	for (char ch: encrypts) {if (c == ch) return true;}
	return false;
}

void checkString(string s, int depth) {
	if (s == message) {
		ans = true;
		ansDepth = depth;
		return;
	}
	if (!ans) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'C') {
				for (int j = i+1; j < s.size(); j++) {
					if (s[j] == 'O') {
						for (int k = j+1; k < s.size(); k++) {
							if (s[k] == 'W') {
								//found possible encryption
								string newString = s.substr(0,i)+s.substr(j+1,k-j-1)+s.substr(i+1,j-i-1)+s.substr(k+1);
								//cout << newString << '\n';
								checkString(newString,depth+1);
							}
						}
					}
				}
			}
		}	
	}
}

int main() 
{	
	//input and setup
	string s; getline(fin,s);
	
	for (char c: message) {
		letterCount[c]++;
	}
	for (char c: s) {
		letterCount[c]--;
	}

	bool isValid = true;
	for (int i = 0; i < 128; i++) {
		if (!isEncrypt((char)i)) {
			if (letterCount[i] != 0) {
				isValid = false;
			}
		}
	}
	//check is message is valid
	int numchars[3] = {0,0,0};
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'C') numchars[0]++;
		if (s[i] == 'O') numchars[1]++;
		if (s[i] == 'W') numchars[2]++;
	}
	isValid = (numchars[0] == numchars[1] && numchars[1] == numchars[2]);
	if (!isValid) {
		cout << "0 0\n";
		fout << "0 0\n";
		return 0;
	}
	
	//now we know message at least has same characters
	checkString(s,0);
	cout << ans << ' ' << ansDepth << '\n';
	fout << ans << ' ' << ansDepth << '\n';
	return 0;
}