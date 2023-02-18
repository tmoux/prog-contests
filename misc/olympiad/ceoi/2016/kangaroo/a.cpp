#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 1e9+7;

void madd(int& a, int b) {
    a += b;
    if (a > M) {
        a -= M;
    }
}

int N;
int dp[maxn][maxn][2]; //0 = go left, 1 = go right
int s, e;

int f(int l, int r, int dir) {
    int& res = dp[l][r][dir];
    if (res >= 0) return res;
    res = 0;
    if (dir == 0) {
        for (int j = 1; 
    }
    else {

    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> N;
    cin >> s >> e;
    int ans = f(s-1,N-s,0);
    madd(ans,f(s-1,N-s,1));
    cout << ans << '\n';
}

