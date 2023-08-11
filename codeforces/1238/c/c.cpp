#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int h, n; cin >> h >> n;
        vector<int> p(n);
        set<int> s;
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            s.insert(p[i]);
        }
        int pos = h;
        int ans = 0;
        while (pos > 2) {
            auto it = s.lower_bound(pos);
            if (it == s.begin()) {
                //done
                break;
            }
            else {
                --it;
                pos = *it + 1;
                //cout << "pos = " << pos << '\n';
                if (pos <= 2) break;
                auto it2 = s.lower_bound(*it);
                if (it2 == s.begin() || *prev(it2) != pos-2) {
                    ans++;
                    pos -= 2;
                    //cout << "adding, new pos = " << pos << '\n';
                }
                else {
                    pos -= 2;
                }
            }
        }
        cout << ans << '\n';
    }
}

