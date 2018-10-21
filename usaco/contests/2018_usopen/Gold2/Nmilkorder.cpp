/*
ID: silxikys
PROG: milkorder
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
#include <set>
using namespace std;
//Slower but easier version!
//(Uses topological sort with the binary search, instead of linear dfs
//to determine cycles)
ofstream fout("milkorder.out");
ifstream fin("milkorder.in");

const int maxn = 100005;
const int maxm = 500005;
int N, M;
vector<int> orders[maxm];
int res[maxn];

bool buildRes(int X) {
	vector<vector<int>> adj(N+1);
	int pred[maxn];
	memset(pred,0,sizeof(pred));
	for (int i = 0; i <= X; i++) {
		for (int j = 0; j < orders[i].size()-1; j++) {
			adj[orders[i][j]].push_back(orders[i][j+1]);
			pred[orders[i][j+1]]++;
		}
	}
	//using first X
	set<int> S;
	for (int i = 1; i <= N; i++) {
		if (pred[i] == 0) {
			S.insert(i);
		}
	}
	for (int i = 0; i < N; i++) {
		if (S.empty()) {
			//means it has cycle, not possible
			return false;
		}
		int v = *S.begin();
		S.erase(S.begin());
		res[i] = v;
		for (int n: adj[v]) {
			pred[n]--;
			if (pred[n] == 0) {
				S.insert(n);
			}
		}
	}
	return true;
}

int main() 
{
	fin >> N >> M;
	for (int i = 0; i < M; i++) {
		int mi; fin >> mi;
		for (int j = 0; j < mi; j++) {
			int a; fin >> a;
			orders[i].push_back(a);
		}
	}

	int low = 0, high = M+1;
	while (low + 1 < high) {
		int mid = (low+high)/2;
		bool poss = buildRes(mid);
		if (poss) {
			low = mid;
		}
		else {
			high = mid;
		}
	}
	
	//now low is the maximal X
	buildRes(low);
	for (int i = 0; i < N; i++) {
		cout << res[i];
		fout << res[i];
		if (i != N-1) {
			cout << ' ';
			fout << ' ';
		}
	}
	cout << '\n';
	fout << '\n';
	return 0;
}