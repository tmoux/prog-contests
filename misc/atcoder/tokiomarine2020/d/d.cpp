#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;

const int maxn = 1<<19;
int N, Q, V[maxn], W[maxn];
int depth[maxn];
ll dp[550][100001];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> V[i] >> W[i];
        depth[i] = depth[i/2] + 1;
    }
    for (int i = 1; i <= N; i++) {
        if (depth[i] > 9) break;
        for (int j = 0; j <= 100000; j++) {
            dp[i][j] = dp[i/2][j];
            if (W[i] <= j) dp[i][j] = max(dp[i][j],dp[i/2][j-W[i]]+V[i]);
            if (j) dp[i][j] = max(dp[i][j],dp[i][j-1]);
        }
    }
    cin >> Q;
    while (Q--) {
        int v, L; cin >> v >> L;
        if (depth[v] <= 9) {
            cout << dp[v][L] << '\n';
        }
        else {
            vector<pair<int,int>> vv;
            do {
                vv.push_back({V[v],W[v]});
                v /= 2;
            } while (depth[v] > 9);
            int n = vv.size();
            ll ans = 0;
            for (int i = 0; i < (1<<n); i++) {
                ll val = 0, wt = 0;
                for (int j = 0; j < n; j++) {
                    if (i & (1<<j)) {
                        val += vv[j].first;
                        wt += vv[j].second;
                    }
                }
                if (wt > L) continue;
                ans = max(ans,dp[v][L-wt]+val);
            }
            cout << ans << '\n';
        }
    }
}
