#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//2^17 <= 10^5

int jmp[19][100000];
int par[100000];
int depth[100000];

int lca(int a, int b) {
	if (depth[a] < depth[b]) {
		swap(a,b);
	}
	//depth[a] <= depth[b]
	for (int i = 18; i >= 0; i--) {
		int to = jmp[i][a];
		if (to != -1 && depth[to] >= depth[b]) {
			a = to;
		}
	}
	if (a == b) {
		return a;
	}
	for (int i = 18; i >= 0; i--) {
		int toA = jmp[i][a];
		int toB = jmp[i][b];
		if (toA != toB) {
			a = toA;
			b = toB;
		}
	}
	return jmp[0][a];
}

int main()
{
	int n; cin >> n;
	int par[100000];
	par[0] = -1;
	depth[0] = 0;
	for (int i = 1; i < n; i++) {
		cin >> par[i];
		depth[i] = depth[par[i]] + 1;
	}		
	for (int i = 0; i < n; i++) {
		jmp[0][i] = par[i];
	}
	for (int i = 1; i < 19; i++) {
		for (int j = 0; j < n; j++) {
			if (jmp[i-1][j] == -1) {
				jmp[i][j] = -1;
			}
			else {
				jmp[i][j] = jmp[i-1][jmp[i-1][j]];
			}
		}
	}
	int q; cin >> q;
	while (q--) {
		int a, b; cin >> a >> b;
		cout << lca(a,b) << '\n';
	}
	
	return 0;
}