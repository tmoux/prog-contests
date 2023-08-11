#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
set<int> adj[maxn];
int n, q;
bool seen[maxn];

void dfs(int i) {
    seen[i] = true;
    for (int j: adj[i]) {
        if (!seen[j]) dfs(j);
    }
}

int main()
{
    //freopen("connect.in","r",stdin); freopen("connect.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    while (q--) {
        char c; cin >> c;
        if (c == '?') {
            int ans = 0;
            memset(seen,0,sizeof seen);
            for (int i = 1; i <= n; i++) {
                if (seen[i]) continue;
                else {
                    dfs(i);
                    ans++;
                }
            }
            cout << ans << '\n';
        }
        else if (c == '+') {
            int a, b; cin >> a >> b;
            adj[a].insert(b);
            adj[b].insert(a);
        }
        else {
            int a, b; cin >> a >> b;
            adj[a].erase(b);
            adj[b].erase(a);
        }
    }
}

