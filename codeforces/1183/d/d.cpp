#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        map<int,int> cnt;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            cnt[ai]++;
        }
        multiset<int> a;
        for (auto p: cnt) {
            a.insert(p.second);
        }
        ll ans = 0;
        for (int i = n; i >= 1; i--) {
            auto it = a.lower_bound(i);
            if (it != a.end()) {
                ans += i;
                a.erase(it);
            }
        }
        cout << ans << '\n';
    }

}

