#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n, m;
vector<int> adj[maxn];

int color[maxn];
const int M = 998244353;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

bool bfs(int i, pair<int,int>& p) {
    queue<int> q;
    q.push(i);
    color[i] = 0;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        p.first++;
        if (color[f] == 0) p.second++;
        for (int j: adj[f]) {
            if (color[j] == !color[f]) continue;
            if (color[j] == color[f]) return false;
            color[j] = !color[f];
            q.push(j);
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            color[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        bool is = true;
        ll ans = 1;
        for (int i = 1; i <= n; i++) {
            if (color[i] != -1) continue;
            else if (adj[i].size() == 0) {
                ans = (ans*3) % M;
                continue;
            }
            pair<int,int> p;
            is &= bfs(i,p);
            ll mult = (modexp(2,p.second) + modexp(2,p.first-p.second)) % M;
            ans = (ans * mult) % M;
            if (!is) break;
        }
        if (!is) {
            cout << 0 << '\n';
        }
        else {
            cout << ans << '\n';
        }
    }

    return 0;
}

