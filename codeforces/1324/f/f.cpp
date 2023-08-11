#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
vector<int> adj[maxn];

int dp1[maxn], dp2[maxn];
void dfs1(int i, int p) {
    dp1[i] = a[i];
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs1(j,i);
        dp1[i] += max(0,dp1[j]);
    }
}
void dfs2(int i, int p) {
    if (i == 0) {
        dp2[i] = dp1[i];
    }
    else {
        dp2[i] = dp1[i] + max(0,dp2[p] - max(0,dp1[i]));
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs2(j,i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (!a[i]) --a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(0,0);
    dfs2(0,0);
    for (int i = 0; i < n; i++) {
        cout << dp2[i] << ' ';
    }
    cout << '\n';
}
