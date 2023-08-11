#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,int> cnt;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ll zeros = 0;
    for (int i = 0; i < n; i++) {
        int pfx = 0, mx = -999999, mn = 0;
        string s; cin >> s;
        for (char c: s) {
            pfx += (c == '(' ? 1 : -1);
            mx = max(mx,pfx);
            mn = min(mn,pfx);
        }
        if (pfx > 0 && mn >= 0) {
            cnt[pfx]++;
        }
        else if (pfx < 0 && mn == pfx) {
            cnt[pfx]++;
        }
        else if (pfx == 0 && mn == 0) {
            zeros++;        
        }
    }
    ll ans = 0LL;
    for (auto& p: cnt) {
        int q = min(cnt[p.first],cnt[-p.first]);
        ans += q;
    }
    ans /= 2;
    zeros /= 2;
    ans += zeros;
    cout << ans << '\n';

    return 0;
}

