/*
ID: silxikys
PROG: superbull
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;

ofstream fout("superbull.out");
ifstream fin("superbull.in");

const int maxn = 2001;
int N;
int xors[maxn];
int dist[maxn][maxn];
int distFromTree[maxn];
bool inTree[maxn];

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> xors[i];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = xors[i] ^ xors[j];
		}
	}
	//PRIM's algorithm; adding MAXIMUM edge lengths rather than MINIMUM edge to build maximal spanning tree with N-1 vertices
	long long total = 0;
	inTree[0] = 1;
	for (int i = 0; i < N; i++) {
		distFromTree[i] = dist[i][0];
	}
	for (int i = 0; i < N - 1; i++) {
		int nextNode = -1, maxdist = -1;
		for (int v = 0; v < N; v++) {
			if (!inTree[v] && distFromTree[v] > maxdist) {
				maxdist = distFromTree[v];
				nextNode = v;
			}
		}
		total += maxdist;
		inTree[nextNode] = 1;
		for (int v = 0; v < N; v++) {
			if (!inTree[v] && dist[v][nextNode] > distFromTree[v]) {
				distFromTree[v] = dist[v][nextNode];
			}
		}
	}

	cout << total << '\n';
	fout << total << '\n';


	return 0;
}