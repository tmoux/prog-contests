#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    ll ans = 0;
    for (int i = 2; i < n; i++) {
        ans += 1LL*i*(i+1);
    }
    cout << ans << '\n';
}

