/*
ID: silxikys
PROG: cowcode
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

ofstream fout("cowcode.out");
ifstream fin("cowcode.in");

int ssize;

long long largefloor(long long N) {
	long long ret = ssize;
	while (ret < N) {
		ret *= 2;
	}
	ret /= 2;
	return ret;
}

int main() 
{
	string s;
	long long N;
	fin >> s >> N;
	ssize = s.size();
	while (N > ssize) {
		long long lf = largefloor(N);
		N -= (lf + 1);
		if (N == 0) {
			N += lf;
		}
	}
	int index = N;
	if (index == 0) {
		index += ssize;
	}
	//cout << index << '\n';
	

	cout << s[index-1] << '\n';
	fout << s[index-1] << '\n';

	//cout << largefloor(6) << '\n';


	return 0;
}