#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a,a+n);
    for (int i = 0; i < n/2; i++) {
        ll b = (a[i] + a[n-1-i]) * (a[i] + a[n-1-i]);
        ans += b;
    }
    cout << ans << '\n';

    return 0;
}

