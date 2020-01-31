#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
vector<int> adj[maxn];

int dp[maxn];
int isc[maxn];

void dfs(int i, int p) {
    int cnt = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        cnt++;
        dfs(j,i);
        dp[i] += dp[j];
        isc[i] |= isc[j];
    }
    if (cnt == 0) {
        dp[i] = 1;
        isc[i] = 0;
    }
    else if (cnt == 1) {

    }
    else {
        if (!isc[i]) {
            dp[i]--;
        }
        isc[i] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    cout << dp[1] << '\n';
}

