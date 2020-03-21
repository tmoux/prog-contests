#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 500005;
int n, a[2*maxn], b[2*maxn];
pair<int,int> dp[2*maxn][2];

pair<int,int> merge(pair<int,int> a, pair<int,int> b) {
    if (a.first == -1) return b;
    if (b.first == -1) return a;
    return {min(a.first,b.first),max(a.second,b.second)};
}

string res;

void recon(int i, int j, int k) {
    if (i == 0) {
        reverse(res.begin(),res.end());
        cout << res << '\n';
        exit(0);
    }
    res += j ? 'B' : 'A';
    if (j == 0) {
        --k;
        if (a[i] >= a[i-1] && dp[i-1][0].first <= k && k <= dp[i-1][0].second) {
            recon(i-1,0,k);
        }
        else {
            recon(i-1,1,k);
        }
    }
    else {
        if (b[i] >= a[i-1] && dp[i-1][0].first <= k && k <= dp[i-1][0].second) {
            recon(i-1,0,k);
        }
        else {
            recon(i-1,1,k);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= 2*n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= 2*n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < 2*maxn; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = {-1,-1};
        }
    }
    dp[0][0] = dp[1][0] = {0,0};
    for (int i = 1;  i <= 2*n; i++) {
        if (a[i] >= a[i-1]) dp[i][0] = merge(dp[i][0],dp[i-1][0]);
        if (a[i] >= b[i-1]) dp[i][0] = merge(dp[i][0],dp[i-1][1]);
        if (dp[i][0].first != -1) {
            ++dp[i][0].first; ++dp[i][0].second;
        }
        if (b[i] >= a[i-1]) dp[i][1] = merge(dp[i][1],dp[i-1][0]);
        if (b[i] >= b[i-1]) dp[i][1] = merge(dp[i][1],dp[i-1][1]);
        //printf("[%d][0]: (%d, %d)\n",i,dp[i][0].first,dp[i][0].second);
        //printf("[%d][1]: (%d, %d)\n",i,dp[i][1].first,dp[i][1].second);
    }
    if (dp[2*n][0].first <= n && n <= dp[2*n][0].second) {
        recon(2*n,0,n);
    }
    else if (dp[2*n][1].first <= n && n <= dp[2*n][1].second) {
        recon(2*n,1,n);
    }
    else {
        cout << -1 << '\n';
    }
}
