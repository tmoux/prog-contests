#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, p, k;
pair<int,vector<int>> a[maxn];

ll dp[2][1<<7][10];

void amax(ll& a, ll b) {
    a = max(a,b);
}

vector<int> empty[1<<7];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> p >> k;
    for (int mask = 0; mask < (1<<p); mask++) {
        for (int j = 0; j < p; j++) {
            if (!(mask&(1<<j))) {
                empty[mask].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; i++) cin >> a[i].first;
    for (int i = 0; i < n; i++) {
        a[i].second.resize(p);
        for (int j = 0; j < p; j++) {
            cin >> a[i].second[j];
        }
    }
    sort(a,a+n,[](auto a, auto b) {
            return a.first > b.first;
            });
    ll ans = 0;
    for (int i = 0; i < k; i++) ans += a[i].first;
    for (int i = n; i >= 0; i--) {
        int o = i&1;
        for (int mask = 0; mask < (1<<p); mask++) {
            for (int ex = 0; ex <= p; ex++) {
                if (i == n) {
                    if (mask == (1<<p)-1)
                        dp[o][mask][ex] = 0;
                    else 
                        dp[o][mask][ex] = -1e18;
                }
                else {
                    dp[o][mask][ex] = dp[o^1][mask][ex];
                    int r = k+ex;
                    if (i < r) {
                        for (int j: empty[mask]) {
                            ll delta = -a[i].first+a[i].second[j]+a[r].first;
                            amax(dp[o][mask][ex],delta+dp[o^1][mask|(1<<j)][ex+1]);
                        }
                    }
                    else {
                        for (int j: empty[mask]) {
                            ll delta = a[i].second[j];
                            amax(dp[o][mask][ex],delta+dp[o^1][mask|(1<<j)][ex]);
                        }
                    }
                }
            }
        }
    }
    ans += dp[0][0][0];
    cout << ans << '\n';
}
