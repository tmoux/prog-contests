#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 35005, maxk = 2005, off = maxk/2;
int n, k;
vector<int> a[maxn];

const ll INF = 1LL<<62;
ll dp[maxn][maxk];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2*k+1; j++) {
            int ai; cin >> ai;
            a[i].push_back(ai);
        }
    }
    random_device device;
    mt19937 gen(device());
    shuffle(a,a+n,gen);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < maxk; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][off] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < maxk; j++) {
            for (int l = 0; l < 2*k+1; l++) {
                if (j+(l-k) < 0 || j+(l-k) >= maxk) continue;
                dp[i+1][j+(l-k)] = min(dp[i+1][j+(l-k)],dp[i][j]+a[i][l]);
            }
        }
    }
    cout << dp[n][off] << '\n';
}
