#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, m;
vector<int> adj[maxn];
int dist[maxn][maxn];

void get_dist(int i) {
	queue<int> q;
	for (int j = 1; j <= n; j++) dist[i][j] = maxn;
	q.push(i);
	dist[i][i] = 0;
	while (!q.empty()) {
		int f = q.front(); q.pop();
		for (int j: adj[f]) {
			if (dist[i][j] > dist[i][f] + 1) {
				dist[i][j] = dist[i][f] + 1;
				q.push(j);
			}
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
    	int a, b; cin >> a >> b;
    	adj[a].push_back(b);
    	adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
    	get_dist(i);
    }
    int s1, t1, l1, s2, t2, l2;
    cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
    auto solve = [&](int s1, int t1, int s2, int t2, int l1, int l2) {
    	int res = -1;
    	for (int a = 1; a <= n; a++) {
    		for (int b = 1; b <= n; b++) {
    			if (dist[s1][a]+dist[a][b]+dist[b][t1] > l1 ||
    				dist[s2][a]+dist[a][b]+dist[b][t2] > l2) continue;
    			res = max(res,m-dist[s1][a]-dist[s2][a]-dist[a][b]-dist[b][t1]-dist[b][t2]);
    		}
    	}
    	if (dist[s1][t1] <= l1 && dist[s2][t2] <= l2) {
    		res = max(res,m-dist[s1][t1]-dist[s2][t2]);
    	}
    	return res;
    };
    int ans = -1;
    ans = max(ans,solve(s1,t1,s2,t2,l1,l2));
    ans = max(ans,solve(t1,s1,s2,t2,l1,l2));
    ans = max(ans,solve(s1,t1,t2,s2,l1,l2));
    ans = max(ans,solve(t1,s1,t2,s2,l1,l2));
    cout << ans << endl;
}

