#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef pair<ll,int> pi;

const int maxn = 305, INF = 1e9+9;
int n, m, l;

int adj[maxn][maxn];

bool seen[maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

int ans[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(ans,-1,sizeof ans);
    cin >> n >> m >> l;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a][b] = c;
        adj[b][a] = c;
    }
    for (int start = 1; start <= n; start++) {
        priority_queue<pi,vector<pi>,less<pi>> pq;
        vector<ll> dist(n+1,-1);
        vector<int> s(n+1,INF);
        vector<bool> seen(n+1,false);
        dist[start] = l;
        s[start] = 0;
        seen[start] = true;
        pq.push(make_pair(0,start));
        while (!pq.empty()) {
            int u = pq.top().second;
            ans[start][u] = s[u];
            pq.pop();
            for (int v = 1; v <= n; v++) {
                if (adj[u][v] <= 0) continue;
                int w = adj[u][v];
                if (s[v] > s[u]) {
                    if (dist[u] - w >= 0) {
                        s[v] = s[u];
                        dist[v] = dist[u] - w;
                    }
                    else if (l - w >= 0) {
                        if (s[v] > s[u] + 1) {
                            s[v] = s[u] + 1;
                            dist[v] = l-w;
                        }
                        else {
                            amax(dist[v],l-w);
                        }
                    }

                }
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v],v));

                }
            }
        }
    }
}

