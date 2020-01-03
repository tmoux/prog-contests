#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 35;
int n;
ll L;
ll c[maxn];
ll cost[maxn];

ll dp[maxn];
ll f(int i) {
    if (i < 0) return 0;
    if (dp[i] != -1) return dp[i];
    if (L & (1<<i)) {
        return dp[i] = cost[i] + f(i-1);
    }
    else {
        return dp[i] = min(f(i-1),cost[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> L;
    for (int i = 0; i < 31; i++) cost[i] = 1LL<<62;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        cost[i] = c[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < 31; j++) {
            cost[j] = min(cost[j],1LL*c[i]*(1LL<<(j-i)));
        }
    }
    /*
    for (int i = 0; i < 31; i++) {
        cout << i << ": " << cost[i] << '\n';
    }
    */
    for (int i = 0; i < 31; i++) {
        if (L & (1<<i)) {
            dp[i] = cost[i] + (i==0?0LL:dp[i-1]);
        }
        else {
            dp[i] = min(cost[i],i==0?0LL:dp[i-1]);
        }
        //cout << i << ": " << dp[i] << '\n';
    }
    cout << dp[30] << '\n';
}

