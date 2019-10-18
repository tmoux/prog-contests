#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
int a[maxn];
vector<int> adj[maxn];

int dist[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll best = 1e18;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            for (int a = 0; a <= n; a++) {
                dist[a] = 999999;
            }
            queue<int> q;
            q.push(i);
            q.push(j);
            dist[i] = dist[j] = 0;
            while (!q.empty()) {
                int f = q.front(); q.pop();
                for (int k: adj[f]) {
                    if (dist[k] > dist[f] + 1) {
                        dist[k] = dist[f] + 1;
                        q.push(k);
                    }
                }
            }
            ll ans = 0;
            for (int k = 1; k <= n; k++) {
                ans += 1LL*a[k]*dist[k];
            }
            cout << i << ' ' << j << ": " << ans << '\n';
            best = min(best,ans);
        }
    }
    cout << best << '\n';
}
