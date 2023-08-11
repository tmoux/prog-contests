#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, sq = (int)(sqrt(maxn)) + 5;
int n, q, a[maxn], dp[sq][maxn];
int block;

/*
int solve(int p, int k) {
    if (p > n) return 0;
    return 1 + solve(p+a[p]+k,k);
}
*/

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    //sqrt decomp
    block = (int)(sqrt(n));
    for (int i = 1; i <= block; i++) {
        for (int j = n; j >= 1; j--) {
            int nx = j + a[j] + i;
            if (nx > n) {
                dp[i][j] = 1;
            }
            else dp[i][j] = dp[i][nx] + 1;
        }
    }
    cin >> q;
    while (q--) {
        int p, k; cin >> p >> k;
        if (k <= block) {
            cout << dp[k][p] << '\n';
        }
        else {
            function<int(int,int)> solve = [&solve](int p, int k)->int {
                return p > n ? 0 : 1 + solve(p+a[p]+k,k);
            };
            cout << solve(p,k) << '\n';
        }
    }

    return 0;
}

