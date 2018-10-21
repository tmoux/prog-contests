/*
ID: silxikys
PROG: multimoo
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

ofstream fout("multimoo.out");
ifstream fin("multimoo.in");
typedef pair<int,int> pii;

int N;
const int maxn = 251;
int id[maxn][maxn];
bool visited[maxn][maxn];



int main() 
{
	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> id[i][j];
		}
	}


	return 0;
}