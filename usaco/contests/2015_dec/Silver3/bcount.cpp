/*
ID: silxikys
PROG: bcount
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

ofstream fout("bcount.out");
ifstream fin("bcount.in");

int N, Q;
const int maxn = 100001;
int ones[maxn], twos[maxn], threes[maxn];

int main() 
{
	fin >> N >> Q;
	for (int i = 1; i <= N; i++) {
		int add1 = 0;
		int add2 = 0;
		int add3 = 0;
		int id; fin >> id;
		switch (id) {
			case 1: add1 = 1;
					break;
			case 2: add2 = 1;
					break;
			case 3: add3 = 1;
					break;
		}
		ones[i] = ones[i-1] + add1;
		twos[i] = twos[i-1] + add2;
		threes[i] = threes[i-1] + add3;
	}

	for (int i = 0; i < Q; i++) {
		int a, b;
		fin >> a >> b;
		fout << (ones[b]-ones[a-1]) << ' ' << (twos[b]-twos[a-1]) << ' ' << (threes[b]-threes[a-1]) << '\n';
		//cout << (ones[b]-ones[a-1]) << ' ' << (twos[b]-twos[a-1]) << ' ' << (threes[b]-threes[a-1]) << '\n';
	}
	return 0;
}