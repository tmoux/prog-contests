#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, M = 1e9+7;
int n, m, A[maxn];
unordered_set<int> adj[maxn];
int degree[maxn], delta[maxn];
vector<int> bigs;

inline void add(int& a, int b) {
	a = (a+b) % M;
}

int getsum(int v) {
	int res = A[v];
	for (int i: bigs) {
		if (adj[v].count(i)) {
			add(res,delta[i]);
		}
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 0; i < n - 1; i++) {
    	int a, b; cin >> a >> b;
    	adj[a].insert(b);
    	adj[b].insert(a);
    	degree[a]++; degree[b]++;
    }

    for (int i = 1; i <= n; i++) {
    	if (degree[i] <= (int)(4*sqrt(n))) {
    		delta[i] = -1;
    	}
    	else {
    		delta[i] = 0;
    		bigs.push_back(i);
    	}
    }

    cin >> m;
    while (m--) {
    	int t, v; cin >> t >> v;
    	if (t == 1) {
    		int r = getsum(v);
    		if (delta[v] == -1) { //smol node
    			for (int j: adj[v]) {
    				add(A[j],r);
    			}
    		}
    		else {
    			add(delta[v],r);
    		}
    	}
    	else {
    		int res = getsum(v);
    		cout << res << '\n';
    	}
    }


    return 0;
}