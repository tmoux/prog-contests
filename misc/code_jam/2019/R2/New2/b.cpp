#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int aa = 1; aa <= t; aa++) {
        cout << "Case #" << aa << ": ";
        int n; cin >> n;
        vector<pair<ll,ll>> ps;
        for (int i = 0; i < n; i++) {
            ll a, b; cin >> a >> b;
            ps.push_back({a,b});
        }
        bool can = true;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ps[i].first >= ps[j].first && 
                    ps[i].second >= ps[j].second) {
                    cout << "IMPOSSIBLE\n";
                    can = false;
                }
            }
        }
        if (can) {
            pair<ll,ll> lo = {0,0};
        }    
    }
}

