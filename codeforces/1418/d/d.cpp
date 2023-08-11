#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;

int getans(set<int>& s, multiset<int>& ms) {
    if (s.size() <= 2) return 0;
    int mx = *s.rbegin();
    int mn = *s.begin();
    int gap = *ms.rbegin();
    return (mx-mn)-gap;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    multiset<int> ms;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        s.insert(ai);
    }
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (next(it) != s.end()) {
            ms.insert(*next(it)-*it);
        }
    }
    cout << getans(s,ms) << '\n';
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 0) {
            auto it = s.upper_bound(x);
            if (it != s.end()) {
                ms.erase(ms.find(*it-x));
            }
            auto it2 = s.lower_bound(x);
            if (it2 != s.begin()) {
                ms.erase(ms.find(x-*prev(it2)));
            }
            if (it != s.end() && it2 != s.begin()) {
                ms.insert(*it-*prev(it2));
            }

            s.erase(x);
        }
        else {
            auto it = s.upper_bound(x);
            auto it2 = s.lower_bound(x);
            if (it != s.end() && it2 != s.begin()) {
                ms.erase(ms.find(*it-*prev(it2)));
            }
            if (it != s.end()) {
                ms.insert(*it-x);
            }
            if (it2 != s.begin()) {
                ms.insert(x-*prev(it2));
            }
            s.insert(x);
        }
        cout << getans(s,ms) << '\n';
    }
}
