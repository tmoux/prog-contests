#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
int n;
vector<int> adj[maxn];
int isBlack[maxn];

void madd(int& a, int b) {
    a = (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int dp[2][maxn];
int f(int i, int c) { //c == 0 = white, 1 = black
    if (dp[c][i] >= 0) return dp[c][i];
    if (c == 1) {
        //require to find a black
        if (isBlack[i]) {
            dp[c][i] = 1;
            for (int j: adj[i]) {
                dp[c][i] = mult(dp[c][i],(f(j,0)+f(j,1))%M);
            }
        }
        else {
            dp[c][i] = 0;
            int prod = 1;
            for (int j: adj[i]) {
                prod = mult(prod,(f(j,0)+f(j,1))%M);
            }
            for (int j: adj[i]) {
                madd(dp[c][i],mult(f(j,1),
                              mult(prod,inverse((f(j,0)+f(j,1))%M))));
            }
        }
    }
    else {
        if (isBlack[i]) {
            dp[c][i] = 0;
        }
        else {
            dp[c][i] = 1;
            for (int j: adj[i]) {
                dp[c][i] = mult(dp[c][i],(f(j,0)+f(j,1))%M);
            }
        }
    }
    //cout << i << ' ' << c << ": " << dp[c][i] << '\n';
    return dp[c][i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> n;
    for (int i = 1; i <= n-1; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    for (int i = 0; i < n; i++) cin >> isBlack[i];
    for (int i = 0; i < n; i++) {
        //cout << i << ": " << isBlack[i] << '\n';
    }
    cout << f(0,1) << '\n';
    

    return 0;
}

