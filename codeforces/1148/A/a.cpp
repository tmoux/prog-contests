#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, c; cin >> a >> b >> c;
    ll ans = 2*c;
    ll mn = min(a,b);
    ans += 2*mn;
    a -= mn;
    b -= mn;
    if (a > 0 || b > 0) ans++;
    cout << ans << '\n';

}

