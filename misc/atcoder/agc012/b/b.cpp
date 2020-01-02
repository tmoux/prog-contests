#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, q;
vector<int> adj[maxn];
int color[maxn];

int a[maxn][11];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cin >> q; 
    deque<pair<int,int>> deq;
    for (int i = 1; i <= q; i++) {
        int v, d, c; cin >> v >> d >> c;
        color[i] = c;
        a[v][d] = i;
        deq.push_front({v,d});
    }
    while (!deq.empty()) {
        auto p = deq.front();
        deq.pop_front();
        int v = p.first;
        int d = p.second;
        if (d > 0) {
            for (int j: adj[v]) {
                if (a[j][d-1] < a[v][d]) {
                    a[j][d-1] = a[v][d];
                    deq.push_front({j,d-1});
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int d = 0; d <= 10; d++) {
            t = max(t,a[i][d]);
        }
        cout << color[t] << '\n';
    }
}

