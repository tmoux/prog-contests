#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];

map<pair<int,int>,int> mp;
int ans[maxn];

void dfs(int i, int p, int c) {
    if (i != p) {
        ans[mp[make_pair(i,p)]] = c;
    }
    int d = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        if (d == c) d++;        
        dfs(j,i,d++);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        mp[make_pair(a,b)] = i;
        mp[make_pair(b,a)] = i;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1,0);
    int res = 0;
    for (int i = 0; i < n-1; i++) {
        res = max(res,ans[i]);
    }
    cout << res << '\n';
    for (int i = 0; i < n-1; i++) {
        cout << ans[i] << '\n';
    }
}

