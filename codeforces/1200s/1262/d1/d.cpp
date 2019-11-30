#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, m;
int a[maxn];
const ll INF = 1e18;

ll dp[maxn][maxn];
int nxt[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(nxt,-1,sizeof nxt);
    for (int i = n; i >= 1; i--) {
        for (int k = 1; k <= n; k++) {
            dp[i][k] = -INF;
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int k = 1; k <= n; k++) {
            if (k == 1) {
                dp[i][k] = a[i];
            }
            else {
                pair<ll,int> best = {0,maxn};
                for (int j = i + 1; j <= n; j++) {
                    if (best.first < dp[j][k-1] + a[i]) {
                        best = {dp[j][k-1]+a[i],j};
                    }
                }
                if (best.first != 0) {
                    dp[i][k] = best.first;
                    nxt[i][k] = best.second;
                }
            }
        }
    } 

    cin >> m;
    while (m--) {
        int k, pos; cin >> k >> pos;
        pair<ll,int> best = {0,maxn};
        for (int i = 1; i <= n; i++) {
            if (best.first < dp[i][k]) {
                best.first = dp[i][k];
                best.second = i;
            }
        }
        int cur = best.second;
        while (pos > 1) {
            cur = nxt[cur][k];
            pos--;
            k--;
        }
        cout << a[cur] << '\n';
    }
}

