#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int C, P, X, L;
vector<int> adj[maxn];
int cnt[maxn];

bool vis[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> C >> P >> X >> L;
    for (int i = 0; i < P; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    queue<int> q;
    q.push(L);
    vis[L] = true;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (int j: adj[f]) {
            if (vis[j]) continue;
            cnt[j]++;
            if (cnt[j]*2 >= adj[j].size()) {
                vis[j] = true;
                q.push(j);
            }
        }
    }
    cout << (vis[X]?"leave":"stay") << '\n';
}
