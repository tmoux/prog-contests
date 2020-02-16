#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 405;
int N, L, X[maxn], T[maxn];
int mxT = 0;

map<int,int> dp[maxn][maxn][2];

int f(int l, int r, int side, int t) {
    if (r-l >= N+1) return -999999;
    if (t > mxT) return 0;
    auto it = dp[l][r][side].find(t);
    if (it != dp[l][r][side].end())
        return dp[l][r][side][t];
    int& res = dp[l][r][side][t];
    res = 0;
    if (side == 0) {
        //left
        ll nt = t + X[l]-X[l-1];
        int add = nt <= T[l-1];
        res = max(res,add+f(l-1,r,0,nt));
        //right
        nt = t + X[r+1]-X[l];
        add = nt <= T[r+1];
        res = max(res,add+f(l,r+1,1,nt));
    }
    else {
        //left
        ll nt = t + X[r]-X[l-1];
        int add = nt <= T[l-1];
        res = max(res,add+f(l-1,r,0,nt));
        //right
        nt = t + X[r+1]-X[r];
        add = nt <= T[r+1];
        res = max(res,add+f(l,r+1,1,nt));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L;
    for (int i = 1; i <= N; i++) {
        cin >> X[i];
        X[i+N+1] = X[i] + L;
    }
    for (int i = 1; i <= N; i++) {
        cin >> T[i];
        T[i+N+1] = T[i];
        mxT = max(mxT,0);
    }
    X[0] = 0;
    X[N+1] = L;
    X[2*(N+1)] = 2*L;
    int ans = f(N+1,N+1,0,0);
    cout << ans << '\n';
}

