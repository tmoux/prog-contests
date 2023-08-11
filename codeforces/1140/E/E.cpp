#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 998244353;
int n, k, a[maxn];
ll dp[maxn];

bool val(int x) {
    return 1 <= x && x <= k;
}

int mult(int& a, int b) {
    return a = (1LL*a*b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i < n; i++) {
        if (val(a[i-1]) && val(a[i+1]) && a[i-1] == a[i+1]) {
            cout << 0 << '\n';
            return 0;
        }
    }
    if (n > 2 && k == 2) {
        cout << 0 << '\n';
        return 0;
    }
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (val(a[i])) dp[i] = dp[i-1];
        else {
            if (i <= 2) {
                if (val(a[i+2])) dp[i] = (1LL*dp[i-1]*(k-1)) % M;
                else dp[i] = (1LL*dp[i-1]*k) % M;
            }    
            else if (i >= n-1) {
                dp[i] = (1LL*dp[i-1]*(k-1)) % M;
            }
            else {
                int x = a[i-2];
                int y = a[i+2];
                if (val(y)) dp[i] = (1LL*dp[i-1]*(k-2)) % M;    
                else {
                    dp[i] = (1LL*dp[i-1]*(k-1)) % M;        
                }
            }
        }
        //cout << i << ": " << dp[i] << '\n';
    }
    cout << dp[n] << '\n';
}

