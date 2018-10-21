/*
ID: silxikys
PROG: closing
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

ofstream fout("closing.out");
ifstream fin("closing.in");

const int maxn = 200002;
int N, M;
int closing[maxn];
string responses[maxn];
int parent[maxn];
vector<int> adjacents[maxn];

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b; fin >> a >> b;
		adjacents[a].push_back(b);
		adjacents[b].push_back(a);
	}
	for (int i = 0; i < N; i++) {
		fin >> closing[N-i-1];
	}
	responses[0] = "YES";
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
	}
	int root = closing[0];
	set<int> included;
	int numConnected = 0;
	for (int i = 0; i < N; i++) {
		numConnected++;
		int u = closing[i];
		included.insert(u);
		for (int v: adjacents[u]) {
			if (included.find(v) != included.end()) {

			}
		}
	}




	return 0;
}