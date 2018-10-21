/*
ID: silxikys
PROG: cowsignal
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

int M, N, K;
const int maxn = 10;
char grid[maxn][maxn];

int main() {
	ofstream fout("cowsignal.out");
	ifstream fin("cowsignal.in");

	//input
	fin >> M >> N >> K;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			fin >> grid[i][j];
		}
	}

	//output
	for (int i = 0; i < M; i++) {
		for (int qwer = 0; qwer < K; qwer++) {
			for (int j = 0; j < N; j++) {
				for (int asdf = 0; asdf < K; asdf++) {
					cout << grid[i][j];
					fout << grid[i][j];
				}
			}
			cout << '\n';
			fout << '\n';
		}
	}

	return 0;
}