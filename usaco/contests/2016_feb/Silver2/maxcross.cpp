/*
ID: silxikys
PROG: maxcross
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

ofstream fout("maxcross.out");
ifstream fin("maxcross.in");

const int maxn = 100001;
int isBroke[maxn];
int N, K, B;

int main() 
{
	fin >> N >> K >> B;
	for (int i = 0; i < B; i++) {
		int a; fin >> a;
		isBroke[a] = 1;
	}
	
	int curr = 0;
	for (int i = 1; i <= K; i++) {
		curr += isBroke[i];
	}
	int minans = curr;
	for (int i = 2; i + K - 1 <= N; i++) {
		curr -= isBroke[i-1];
		curr += isBroke[i+K-1];
		minans = min(minans,curr);
	}

	cout << minans << '\n';
	fout << minans << '\n';


	return 0;
}