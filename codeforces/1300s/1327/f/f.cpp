#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5, maxk = 31, M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int sub(int a, int b) {
    madd(a,M-b);
    return a;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int n, k, m;
int dp[maxn];
int l[maxn], r[maxn], x[maxn];

int has1[maxn];
int L[maxn];

int solve(int j) {
    memset(has1,0,sizeof has1);
    memset(L,0,sizeof L);
    for (int i = 0; i < m; i++) {
        if (x[i] & (1<<j)) {
            ++has1[l[i]];
            --has1[r[i]+1];
        }
        else {
            L[r[i]+1] = max(L[r[i]+1],l[i]);
        }
    }
    for (int i = 1; i <= n+1; i++) {
        has1[i] += has1[i-1];
        L[i] = max(L[i],L[i-1]);
    }
    dp[0] = 1;
    for (int i = 1; i <= n+1; i++) {
        if (has1[i]) dp[i] = 0;
        else dp[i] = sub(dp[i-1],L[i]?dp[L[i]-1]:0);
        madd(dp[i],dp[i-1]);
    }
    int ans = sub(dp[n+1],dp[n]);
    return ans;
}

int main() {
    scanf("%d %d %d",&n,&k,&m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d\n",l+i,r+i,x+i);
    }
    int res = 1;
    for (int i = 0; i < k; i++) {
        res = mult(res,solve(i));
    }
    printf("%d\n",res);
}

