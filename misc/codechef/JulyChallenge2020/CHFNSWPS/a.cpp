#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<int,int> ma, mb;
        set<int> s;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            s.insert(ai);
            ma[ai]++;
        }
        for (int i = 0; i < n; i++) {
            int bi; cin >> bi;
            s.insert(bi);
            mb[bi]++;
        }
        vector<int> a, b;
        bool poss = true;
        for (auto i: s) {
            if (ma[i] > mb[i]) {
                int diff = ma[i]-mb[i];
                if (diff % 2 != 0) {
                    poss = false;
                    break;
                }
                for (int j = 0; j < diff/2; j++) {
                    a.push_back(i);
                }
            }
            else if (mb[i] > ma[i]) {
                int diff = mb[i]-ma[i];
                if (diff % 2 != 0) {
                    poss = false;
                    break;
                }
                for (int j = 0; j < diff/2; j++) {
                    b.push_back(i);
                }
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            int mn = *s.begin();
            reverse(b.begin(),b.end());
            assert(a.size() == b.size());
            ll ans = 0;
            for (int i = 0; i < a.size(); i++) {
                ans += min(min(a[i],b[i]),2*mn);
            }
            cout << ans << '\n';
        }
    }
}
