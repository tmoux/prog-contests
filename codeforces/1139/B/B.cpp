#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    int curr = 1000000007;
    for (int i = n - 1; i >= 0; i--) {
        curr = min(max(0,curr-1),a[i]);
        ans += curr;
    }
    cout << ans << '\n';
}

