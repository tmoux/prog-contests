#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 22;
int N, a[maxn][maxn];
const int M = 1e9+7;
int dp[maxn][1<<maxn];

void madd(int& a, int b) {
    a += b;
    while (a > M) a -= M;
}

int f(int i, int mask) {
    if (i == N) return 1;
    if (dp[i][mask] != -1) return dp[i][mask];
    dp[i][mask] = 0;
    for (int j = 0; j < N; j++) {
        if (!((1<<j) & mask) && a[i][j]) {
            madd(dp[i][mask],f(i+1,mask|(1<<j)));            
        }
    }
    return dp[i][mask];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> N;
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            cin >> a[i][j];
    cout << f(0,0) << '\n';
    return 0;
}

