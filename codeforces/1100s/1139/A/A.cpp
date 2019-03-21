#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll ans = 0;
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        int c = (s[i] - '0');
        if (c % 2 == 0) {
            ans += (i+1);
        }
    }
    cout << ans << '\n';
}

