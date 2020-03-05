#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, k;
vector<int> adj[maxn], rev[maxn];
vector<int> p;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[b].push_back(a);
        rev[a].push_back(b);
    }
    cin >> k;
    for (int i = 0; i < k; i++) {
        int pi; cin >> pi;
        p.push_back(pi);
    }
    int t = p.back();
    vector<int> dist(n+1,maxn);
    queue<int> q;
    dist[t] = 0;
    q.push(t);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (auto j: adj[f]) {
            if (dist[j] > dist[f] + 1) {
                dist[j] = dist[f] + 1;
                q.push(j);
            }
        }
    }
    int mn = 0, mx = 0;
    for (int i = 1; i < p.size(); i++) {
        int dd = dist[p[i-1]];
        if (dist[p[i]] > dd-1) {
            mn++;
            mx++;
        }
        else {
            bool flag = false;
            for (auto j: rev[p[i-1]]) {
                if (j == p[i]) continue;
                if (dist[j] == dist[p[i]]) {
                    flag = true;
                    break;
                }
            }
            if (flag) mx++;
        }
    }
    cout << mn << ' ' << mx << endl;
}
