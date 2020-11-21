#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 2e5+5;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n), b(k);
        map<int,int> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mp[a[i]] = i;
            a[i] = i;
        }
        set<int> bs;
        for (int i = 0; i < k; i++) {
            cin >> b[i];
            b[i] = mp[b[i]];
            bs.insert(b[i]);
        }
        int ans = 1;
        set<int> as;
        for (int i = 0; i < n; i++) as.insert(i);
        for (int i = 0; i < k; i++) {
            auto it = as.find(b[i]);
            int cnt = 0;
            int rem = -1;
            if (it != as.begin() && !bs.count(*prev(it))) {
                cnt++;
                rem = *prev(it);
            }
            if (next(it) != as.end() && !bs.count(*next(it))) {
                cnt++;
                rem = *next(it);
            }
            /*
            for (auto j: as) {
                cout << j << ' ';
            }
            cout << '\n';
            cout << i << ": " << b[i] << ' ' << cnt << '\n';
            cout << "rem = " << rem << endl;
            */
            ans = (1LL*ans*cnt) % M;
            bs.erase(b[i]);
            if (rem != -1) as.erase(rem);
            if (ans == 0) break;
        }
        cout << ans << '\n';
    }
}
