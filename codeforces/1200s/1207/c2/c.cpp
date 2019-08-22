#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t; cin >> t;
    while (t--) {
        ll n, a, b; cin >> n >> a >> b;
        string s; cin >> s;
        vector<pair<char,ll>> vec;
        char curr = s[0];
        ll len = 1;
        for (ll i = 1; i < s.size(); i++) {
            if (s[i] != curr) {
                vec.push_back({curr,len});
                curr = s[i];
                len = 1;
            }
            else {
                len++;
            }
        }
        vec.push_back({curr,len});
        ll ans = 1LL*n*a + 1LL*(n+1)*b;
        if (vec.size() == 1) {
            cout << ans << '\n';
            continue;
        }
        for (ll i = 0; i < vec.size(); i++) {
            auto p = vec[i];
            /*
            cout << ans << '\n';
            cout << p.first << ' ' << p.second << '\n';
            */
            if (i == 0 || i == vec.size()-1) {
                ans += a;
            }
            else if (p.first == '1') {
                ans += 1LL*(p.second+1)*b;
            }
            else {
                //gaps
                assert(p.first == '0');
                ans += min(2*a,1LL*(p.second-1)*b);
            }
        }
        cout << ans << '\n';
    }
}

