#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e4+4;
int n, m;
vector<int> adj[maxn];
int dist[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    while (t--) {
    	cin >> n >> m;
    	for (int i = 1; i <= n; i++) adj[i].clear();
    	memset(dist,-1,sizeof dist);
    	for (int i = 0; i < m; i++) {
    		int u, v; cin >> u >> v;
    		adj[u].push_back(v);
    		adj[v].push_back(u);
    	}
    	queue<int> q;
    	q.push(1);
    	dist[1] = 0;
    	while (!q.empty()) {
    		int f = q.front();
    		for (int j: adj[f]) {
    			if (dist[j] == -1) {
    				dist[j] = dist[f] + 1;
    				q.push(j);
    			}
    		}
    		q.pop();
    	}
    	cout << dist[n] << '\n';
    }

    return 0;
}