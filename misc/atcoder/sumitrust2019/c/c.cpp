#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x; cin >> x;
    dp[0] = 1;
    for (int i = 0; i <= x; i++) {
        if (dp[i] == 1) {
            dp[i+100] = 1;
            dp[i+101] = 1;
            dp[i+102] = 1;
            dp[i+103] = 1;
            dp[i+104] = 1;
            dp[i+105] = 1;
        }
    }
    cout << dp[x] << '\n';
}

