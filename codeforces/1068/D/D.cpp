#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxx = 205, M = 998244353;
int n, A[maxn];
int dp[2][maxx][maxn];
int pfx[2][maxx];
void add(int& a, int b) { a = (a + b) % M;}

int gsum(int a, int l, int r) {
    return (pfx[a][r] - pfx[a][l-1] + M) % M;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    memset(dp,0,sizeof dp);
    for (int i = 1; i <= 200; i++) {
        if (A[1] == -1 || i == A[1]) {
            dp[0][i][1] = 1;            
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int a: {0,1}) {
            for (int x = 1; x <= 200; x++) {
                pfx[a][x] = dp[a][x][i-1];
                add(pfx[a][x],pfx[a][x-1]);
            }
        }
        for (int a: {0,1}) {
            for (int x = 1; x <= 200; x++) {
                if (A[i] == -1 || A[i] == x) {
                    if (a == 0) {
                        dp[a][x][i] = (gsum(0,1,x-1) + gsum(1,1,x-1)) % M;
                    }
                    else {
                        dp[a][x][i] = (gsum(1,x,200) + gsum(0,x,x)) % M;
                    }
                }
            }
        }
    }

    int r = 0;
    for (int x = 1; x <= 200; x++) {
        add(r,dp[1][x][n]);
    }
    cout << r << '\n';

    return 0;
}

