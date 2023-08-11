#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3000, M = 998244353;
int n, m;
string S, T;
int madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> S >> T;
    n = S.size();
    m = T.size();
    for (int gap = n-1; gap >= 0; gap--) {
        for (int l = 0; l+gap < n; l++) {
            int r = l+gap;
            dp[l][r] = l == 0 && r >= m-1;
            int idx = r-l+1;
            if (l-1 >= 0 && (l-1 >= m || S[idx] == T[l-1]))
                madd(dp[l][r],dp[l-1][r]);
            if (r+1 < n && (r+1 >= m || S[idx] == T[r+1]))
                madd(dp[l][r],dp[l][r+1]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i >= m || S[0] == T[i])
            madd(ans,dp[i][i]);
    }
    cout << mult(ans,2) << '\n';
}
