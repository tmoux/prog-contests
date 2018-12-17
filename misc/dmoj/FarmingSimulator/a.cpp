#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> a(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    sort(a.begin(),a.end());
    for (int i = 0; i < m; i++) {
        ans -= a[i];
    }
    cout << ans << '\n';

    return 0;
}

