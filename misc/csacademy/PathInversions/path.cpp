#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 1e9+7, maxn = 1e5+5;
int N, K;
vector<int> adj[maxn];
ll ans = 0;

struct Node
{
	vector<int>* vec;
	inline int sz() { return vec->size(); }
	Node() {
		vec = new vector<int>;
	}
	void addSelf() {
		vec->push_back(1);
	}
};

void merge(Node& a, Node& b) {
	if (a.sz() < b.sz()) swap(a,b);
	int diff = a.sz() - b.sz();
	if (b.sz() == 0 && a.sz() >= K) {
		ans = (ans + 1) % M;
	}
	for (int i = 0; i < b.sz(); i++) {
		int d1 = b.sz() - i;
		if (d1 == K) {
			ans = (ans + (*b.vec)[i]) % M;
			continue;
		}
		int d2 = K - d1;
		if (a.sz() - d2 >= 0) {
			ans = (ans + ((ll)((*b.vec)[i])*(*a.vec)[a.sz()-d2])%M)%M;
		}
	}

	for (int i = 0; i < b.sz(); i++) {
		(*a.vec)[i+diff] += (*b.vec)[i];
	}
}

Node* dfs(int i, int par) {
	Node* ni = new Node();
	for (int j: adj[i]) {
		if (j == par) continue;
		Node* nj = dfs(j,i);
		merge(*ni,*nj);
		delete nj;
	}
	ni->addSelf();
	return ni;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif

    cin >> N >> K;
    for (int i = 0; i < N - 1; i++) {
    	int u, v; cin >> u >> v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    dfs(1,1);
    ans = (((ll)(K+1)*K/2)%M) * ans % M;
    cout << ans << '\n';

    return 0;
}