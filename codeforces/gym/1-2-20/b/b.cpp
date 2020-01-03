#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, a[maxn];

int dp[maxn][maxn];

int amin(int& a, int b) {
    a = min(a,b);
}

int nxt[maxn][maxn];

int f(int i, int j) {
    int& res = dp[i][j];
    if (res != -1) return res;
    if (j == (n+1)/2) {
        if (n&1) return res = a[i];
        else return res = max(a[i],a[n]);
    }
    int a1 = a[2*j], a2 = a[2*j+1];
    res = f(i,j+1)+max(a1,a2);
    amin(res,f(2*j,j+1)+max(a[i],a2));
    amin(res,f(2*j+1,j+1)+max(a[i],a1));
    return res;
}

void recon(int i, int j, int ans) {
    if (j == (n+1)/2) {
        if (n&1) cout << i << '\n';
        else cout << i << ' ' << n << '\n';
        return;
    }
    int a1 = a[2*j], a2 = a[2*j+1];
    if (ans == f(i,j+1)+max(a1,a2)) {
        cout << 2*j << ' ' << 2*j+1 << '\n';
        recon(i,j+1,ans-max(a1,a2));
    }
    else if (ans == f(2*j,j+1)+max(a[i],a2)) {
        cout << i << ' ' << 2*j+1 << '\n';
        recon(2*j,j+1,ans-max(a[i],a2));
    }
    else {
        cout << i << ' ' << 2*j << '\n';
        recon(2*j+1,j+1,ans-max(a[i],a1));
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp,-1,sizeof dp);
    int ans = f(1,1);
    cout << ans << '\n';
    recon(1,1,ans);
}

