/*
ID: silxikys
PROG: censor
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
using namespace std;

ofstream fout("censor.out");
ifstream fin("censor.in");

string S, T;
const long long MOD = (1 << 30) - 1;
const int alsize = 26 ;

int convert(char c) {return c-'a';}

int main() 
{
	fin >> S >> T;
	bool foundAny = true;
	long long Thash = 0;
	for (char c: T) {
		Thash = (Thash*alsize + convert(c)) % MOD;
	}
	string build;
	long long Tbase = (int)pow(alsize,T.size()-1);
	long long hash = 0;
	int hashlength = 0;
	for (int i = 0; i < S.size(); i++) {
		build += S[i];
		if (build.size() <= T.size()) {
			hash = (hash*alsize + convert(S[i])) % MOD;
		}
		else {
			hash -= (Tbase*convert(build[build.size()-1-T.size()]));
			hash = (hash*alsize + convert(S[i])) % MOD;
		}
		cout << hash << '\n';
		if (hash == Thash && build.substr(build.size()-T.size()) == T) {
			build.erase(build.end()-T.size(),build.end());
			hash = 0;
			for (int j = build.size() - T.size(); j < build.size(); j++) {
				hash = (hash*alsize + convert(S[j])) % MOD;
			}
		}
	}

	cout << build << '\n';
	fout << build << '\n';

	return 0;
}