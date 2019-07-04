#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005, maxk = 5;
int n, k, a[maxn];

int pos[5][maxn];

vector<int> to[maxn];
int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (j == 0) a[i] = ai;
            pos[j][ai] = i;
            //cout << j << ' ' << ai << ": " << pos[j][ai] << '\n';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool poss = true;
            for (int q = 1; q < k; q++) {
                if (pos[q][a[i]] > pos[q][a[j]]) {
                    poss = false;
                    break;
                }
            }
            if (poss) {
                to[a[i]].push_back(a[j]);
                //cout << a[i] << ' ' << a[j] << '\n';
            }
        }
    }
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[a[i]] = 1;
        for (int j: to[a[i]]) {
            dp[a[i]] = max(dp[a[i]],dp[j]+1);
        }
        ans = max(ans,dp[a[i]]);
    }
    cout << ans << '\n';
}

