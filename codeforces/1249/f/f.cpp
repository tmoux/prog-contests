#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 205;
int n, k, a[N];
vector<int> adj[N];
int dp[N][N];

void dfs(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    for (int d = 0; d < n; d++) {
        if (d == 0) {
            dp[i][d] = a[i];
            for (int j: adj[i]) {
                if (j == p) continue;
                dp[i][d] += dp[j][k-1];
            }
        }
        else {
            for (int j: adj[i]) {
                if (j == p) continue;
                int c = dp[j][d-1];
                for (int h: adj[i]) {
                    if (h == p || h == j) continue;
                    c += dp[h][max(d-1,k-d-1)];
                }
                dp[i][d] = max(dp[i][d],c);
            }
        }
    }
    for (int d = n-1; d > 0; d--) {
        dp[i][d-1] = max(dp[i][d-1],dp[i][d]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k; k++;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    cout << dp[1][0] << '\n';
}

