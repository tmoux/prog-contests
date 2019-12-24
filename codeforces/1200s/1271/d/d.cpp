#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, m, k;
int a[maxn], b[maxn], c[maxn];
const int INF = 1e9;

int latest[maxn];
vector<int> dir[maxn];

int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        latest[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        latest[v] = max(latest[v],u);
    }
    for (int i = 1; i <= n; i++) {
        dir[latest[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        sort(dir[i].begin(),dir[i].end(),[](auto i, auto j) {
                return c[i] > c[j];
                });
    }
    for (int j = 0; j <= 5000; j++) {
        dp[n+1][j] = 0;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < a[i]; j++) {
            dp[i][j] = -INF;
        }
        for (int j = a[i]; j <= 5000; j++) {
            int cur = j + b[i];
            int val = 0;
            dp[i][j] = dp[i+1][cur];
            for (int k = 0; k < dir[i].size(); k++) {
                val += c[dir[i][k]];
                cur--;
                if (cur >= 0) dp[i][j] = max(dp[i][j],val+dp[i+1][cur]);
            }
        }
    }
    cout << (dp[1][k] >= 0 ? dp[1][k] : -1) << '\n';
}

