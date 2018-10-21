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
using namespace std;

ofstream fout("censor.out");
ifstream fin("censor.in");

string S, T;


int main() 
{
	fin >> S >> T;
	bool foundAny = true;
	while (foundAny) {
		foundAny = false;
		for (int i = 0; i + T.size() < S.size(); i++) {
			string substr = S.substr(i,T.size());
			//cout << substr << '\n';
			if (substr == T) {
				S.erase(i,T.size());
				foundAny = true;
				break;
			}
		}
	}

	cout << S << '\n';
	fout << S << '\n';


	return 0;
}