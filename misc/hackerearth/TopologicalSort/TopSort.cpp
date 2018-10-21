#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;
const int maxn = 20;
int N, M;

bool topSort(int n, vector<int> adj[], int res[]) {
	//returns lexicographically minimal sort to res array
	int pred[maxn+5];
	memset(pred,0,sizeof(pred));
	//nodes from [1,n]
	for (int i = 1; i <= n; i++) {
		for (int j: adj[i]) {
			pred[j]++;
		}
	}
	set<int> S;
	for (int i = 1; i <= n; i++) {
		if (pred[i] == 0) {
			S.insert(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (S.empty()) {
			//means graph is cyclic, no top sort possible
			return false;
		}
		int v = *S.begin();
		S.erase(S.begin());
		res[i] = v;
		for (int j: adj[v]) {
			pred[j]--;
			if (pred[j] == 0) {
				S.insert(j);
			}
		}
	}
	return true;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> N >> M;
	vector<int> adj[maxn+5];
	for (int i = 0; i < M; i++) {
		int X, Y; cin >> X >> Y;
		adj[X].push_back(Y);
	}
	int res[maxn+5];
	topSort(N,adj,res);
	for (int i = 0; i < N; i++) {
		cout << res[i] ;
		if (i != N-1) cout << ' ';
	}
	cout << '\n';
	
	return 0;
}