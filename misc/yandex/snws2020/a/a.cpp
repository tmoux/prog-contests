#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, a[maxn];
ll x[maxn], y[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        x[i] = x[i-1] + a[i]*a[i];
    }
    for (int i = n; i >= 1; i--) {
        y[i] = y[i+1] + a[i];
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        //cout << i << ": " << x[i]*y[i+1] << '\n';
        ans = max(ans,x[i]*y[i+1]);
    }
    cout << ans << '\n';
}

