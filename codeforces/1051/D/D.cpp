#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1010, M = 998244353;
int n, k;
ll dp[2][2][maxn][2*maxn];

ll f(bool a, bool b, int i, int j) {
    if (j > k) return 0;
    if (i == n) {
        j += (a^b) ? 2 : 1;
        return (j == k) ? 1 : 0;
    }
    ll& res = dp[a][b][i][j];
    if (res >= 0) return res;
    res = 0;
    if (a^b) {
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                if (x == a && y == b) res = (res + f(x,y,i+1,j)) % M;
                else if (x^y) res = (res + f(x,y,i+1,j+2)) % M;
                else res = (res + f(x,y,i+1,j+1)) % M;
            }
        }
    }
    else {
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                if (x == a && y == b) res = (res + f(x,y,i+1,j)) % M;
                else if (x^y) res = (res + f(x,y,i+1,j)) % M;
                else res = (res + f(x,y,i+1,j+1)) % M;
            }
        }
    }
    //cout << a << ' ' << b << ' ' << i << ' ' << j << ' ' << res << '\n';
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1LL,sizeof dp);
    cin >> n >> k;
    ll res = 0LL;
    for (int i = 0; i < 4; i++) {
        res = (res + f((i>>1)&1,i&1,1,0)) % M;
        //cout << ((i>>1)&1) << ' ' << (i&1) << ' ' << f((i>>1)&1,i&1,1,0) << '\n';
    }
    cout << res << '\n';

    return 0;
}

