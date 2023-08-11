#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505, M = 998244353;
int n, m;
int c[maxn];

void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int dp[maxn][maxn];
int f(int l, int r) {
    if (l >= r) return 1;
    if (dp[l][r] >= 0) return dp[l][r];
    pair<int,int> lowest = {n+1,-1};
    for (int i = l; i <= r; i++) {
        lowest = min(lowest,{c[i],i});    
    }
    int split = lowest.second;
    int s1 = 0;
    for (int a = l; a <= split; a++) {
        madd(s1,mult(f(l,a-1),f(a,split-1)));        
    }
    int s2 = 0;
    for (int b = split; b <= r; b++) {
        madd(s2,mult(f(split+1,b),f(b+1,r)));
    }
    dp[l][r] = mult(s1,s2);
    return dp[l][r];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> c[i];
    }
    cout << f(1,n) << '\n';
}

