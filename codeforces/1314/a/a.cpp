#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<ll> a(n);
    vector<ll> t(n);
    map<ll,vector<ll>> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        mp[a[i]].push_back(t[i]);
    }
    multiset<ll> ms;
    ll sum = 0;
    ll ans = 0;
    for (ll i = 1; ;) {
        //cout << "i = " << i << endl;
        if (ms.empty() && !mp.count(i)) {
            auto ni = mp.lower_bound(i);
            if (ni == mp.end()) break;
            //cout << i << ": " << ni->first << '\n';
            i = ni->first;
        }
        else {
            for (auto j: mp[i]) {
                ms.insert(j);
                sum += j;
            }
            if (!ms.empty()) {
                auto it = prev(ms.end());
                sum -= *it;
                ms.erase(it);
            }
            /*
            cout << i << ": ";
            for (auto j: ms) {
                cout << j << ' ';
            }
            cout << '\n';
            */
            ans += sum;
            ++i;
        }
    }
    cout << ans << '\n';
}
