#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sum -= a[0];
    ll ans = abs(sum - a[0]);
    ll curr = a[0];
    for (int i = 1; i < n - 1; i++) {
        curr += a[i];
        sum -= a[i];
        ans = min(ans,abs(curr-sum));
    }
    cout << ans << '\n';
}

