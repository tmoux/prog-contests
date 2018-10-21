#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 17;
int n, L, nleft[maxn], par[maxk][maxn]; 
ll S, weight[maxn], chain[maxn];
vector<int> child[maxn];
int ans = 0;

inline int lg(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

int f(int i) { //returns max number of nodes that can be added to the chain
	int d = 0, curr = i;
	ll w = chain[i];
	for (int k = lg(nleft[i]); k >= 0; k--) {
		if (d + (1 << k) > nleft[i] || par[k][curr] == 0) continue;
		ll poss = w + (weight[par[0][i]] - weight[par[0][par[k][curr]]]);
		if (poss <= S) {
			d += (1 << k);
			w = poss;
			curr = par[k][curr];
		}
	}
	return d;
}

void dfs(int i) {
	if (child[i].empty()) {
		nleft[i] = L-1;
		chain[i] = weight[i] - weight[par[0][i]];
		return;
	}
	int maxUp = 0, which = -1;
	for (int j: child[i]) {
		dfs(j);
		int r = f(j);
		if (r > maxUp) {
			maxUp = r;
			which = j;
		}
	}
	if (which == -1) {
		nleft[i] = L-1;
		chain[i] = weight[i] - weight[par[0][i]];
	}
	else {
		nleft[i] = nleft[which] - 1;
		chain[i] = chain[which] + (weight[i] - weight[par[0][i]]);
	}
	int add = child[i].size() - (which == -1 ? 0 : 1);
	ans += add;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> L >> S;
    for (int i = 1; i <= n; i++) {
    	cin >> weight[i];
    	if (weight[i] > S) {
    		cout << "-1\n";
    		return 0;
    	}
    }
    for (int i = 2; i <= n; i++) {
    	int pi; cin >> pi;
    	child[pi].push_back(i);
    	//cout << pi << ' ' << i << '\n';
    	par[0][i] = pi;
    	weight[i] += weight[pi];
    }
    //sparse table precomp
    for (int k = 1; k <= lg(n); k++) {
    	for (int i = 1; i <= n; i++) {
    		if (par[k-1][i] == 0) par[k][i] = 0;
    		else par[k][i] = par[k-1][par[k-1][i]];
    	}
    }
    dfs(1);
    cout << (ans+1) << '\n';
    return 0;
}
