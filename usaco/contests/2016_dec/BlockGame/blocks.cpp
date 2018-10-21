/*
ID: silxikys
PROG: blocks
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int maxn = 100;
string spellboards[maxn][2];
int N;
int masteralpha[26];

int main() {
	ofstream fout("blocks.out");
	ifstream fin("blocks.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			fin >> spellboards[i][j];
		}
	}


	//calculation
	for (int i = 0; i < N; i++) {
		int alphabet[26] = {0};
		for (int word = 0; word < 2; word++) {
			int talpha[26] = {0};
			for (char c: spellboards[i][word]) {
				talpha[c-'a']++;
			}
			for (int a = 0; a < 26; a++) {
				alphabet[a] = max(alphabet[a],talpha[a]);
			}
		}
		for (int b = 0; b < 26; b++) {
			masteralpha[b] += alphabet[b];
		}
	}

	for (int i = 0; i < 26; i++) {
		cout << masteralpha[i] << '\n';
		fout << masteralpha[i] << '\n';
	}

	return 0;
}