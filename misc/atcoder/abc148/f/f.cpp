#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, u, v;
vector<int> adj[maxn];
int d1[maxn], d2[maxn];

pair<int,int> furthest = {-1,-1};
bool seen[maxn];
void dfs(int i, int d) {
    furthest = max(furthest,{d2[i],i});
    seen[i] = true;
    for (int j: adj[i]) {
        if (d1[j] < d2[j] && !seen[j]) {
            dfs(j,d+1);
        }
    }
}

int main() {
    cin >> n >> u >> v;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        d1[i] = maxn;
        d2[i] = maxn;
    }
    d1[u] = 0;
    d2[v] = 0;
    q.push(u);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (int j: adj[f]) {
            if (d1[j] > d1[f] + 1) {
                d1[j] = d1[f] + 1;
                q.push(j);
            }
        }
    }
    q.push(v);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (int j: adj[f]) {
            if (d2[j] > d2[f] + 1) {
                d2[j] = d2[f] + 1;
                q.push(j);
            }
        }
    }
    dfs(u,0);
    int ans = d1[furthest.second];
    int d = d2[furthest.second] - d1[furthest.second];
    for (int i = 0; ; i++) {
        if (i % 2 == 0) {
            if (i % 4 == 0) d--;
            else d++;
        }
        else {
            d--;
            ans++;
        }
        if (d == 0) break;
    }
    cout << ans << endl;
}
