#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int N, X, S[maxn];

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) b >>= 1;
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int dp[100005][maxn];
int inv[maxn];

int f(int x, int i) {
    int& res = dp[x][i];
    if (res != -1) return res;
    if (i == N) return res = x;
    res = mult(mult(N-i-1,inv[N-i]),f(x,i+1));
    madd(res,mult(mult(1,inv[N-i]),f(x%S[i],i+1)));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> X;
    for (int i = 1; i <= N; i++) {
        inv[i] = inverse(i);
        cin >> S[i-1];
    }
    sort(S,S+N,greater<int>());
    memset(dp,-1,sizeof dp); 
    int ans = f(X,0);
    /*
    for (int i = 1; i <= N; i++) {
        ans = mult(ans,i);
    }
    */
    cout << ans << '\n';
}
