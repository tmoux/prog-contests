#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int b, p, f; cin >> b >> p >> f;
        int h, c; cin >> h >> c;
        ll ans = 0;
        for (int i = 0; i <= p; i++) {
            if (i <= b/2) {
                int beef = i;
                int curr = b-2*beef;
                int chicken = max(0,min(f,curr/2));
                ll res = 1LL*beef*h + 1LL*chicken*c;
                //cout << beef << ' ' << chicken << ": " << res << '\n';
                ans = max(ans,res);
            }
        }
        cout << ans << '\n';
    }
}

