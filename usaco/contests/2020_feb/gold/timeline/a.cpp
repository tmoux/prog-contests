#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, M, C;
int S[maxn]; 
vector<pair<int,int>> edges[maxn];
vector<int> adj[maxn];
int deg[maxn];
int ans[maxn];

int main()
{
    freopen("timeline.in","r",stdin); freopen("timeline.out","w",stdout);
    cin >> N >> M >> C;
    for (int i = 1; i <= N; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < C; i++) {
        int a, b, x; cin >> a >> b >> x;
        edges[b].push_back({a,x});
        adj[a].push_back(b);
        ++deg[b];
    }
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int i = q.front(); q.pop();
        ans[i] = S[i];
        for (auto p: edges[i]) {
            ans[i] = max(ans[i],ans[p.first]+p.second);
        }
        for (int j: adj[i]) {
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << '\n';
    }
}
