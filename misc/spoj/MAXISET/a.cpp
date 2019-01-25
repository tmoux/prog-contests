#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 45;
bool adj[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
    	int n, m; cin >> n >> m;
    	vector<int> perm;
    	memset(adj,0,sizeof adj);
    	for (int i = 1; i <= n; i++) {
    		perm.push_back(i);
    	}
    	while (m--) {
    		int u, v; cin >> u >> v;
    		adj[u][v] = true;
    		adj[v][u] = true;
    	}
    	int ans = 0;
    	for (int i = 0; i < 100000; i++) {
    		random_shuffle(perm.begin(),perm.end());
    		vector<int> ch;
    		for (int j: perm) {
    			bool poss = true;
    			for (int k: ch) {
    				if (j == k || adj[j][k]) {
    					poss = false;
    					break;
    				}
    			}
    			if (poss) ch.push_back(j);
    		}
    		ans = max(ans,(int)ch.size());
    	}
    	cout << ans << '\n';
    }


    return 0;
}