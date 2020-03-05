#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, p, q, s;
vector<int> ps, qs;

bool poss(int d) {
    multiset<int> ms;
    for (int i: qs) ms.insert(i);
    int cnt = 0;
    for (int i: ps) {
        auto it = ms.upper_bound(min(s-i,i+d));
        if (it != ms.begin() && abs(i-*prev(it) <= d)) {
            ms.erase(prev(it));
            cnt++;
        }
    }
    return cnt >= n;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> p >> q >> s;
    for (int i = 0; i < p; i++) {
        int ai; cin >> ai; ps.push_back(ai);
    }
    sort(ps.begin(),ps.end(),greater<int>());
    for (int i = 0; i < q; i++) {
        int ai; cin >> ai; qs.push_back(ai);
    }
    int lo = -1, hi = 1e9+9;
    if (!poss(hi)) {
        cout << -1 << endl;
        return 0;
    }
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (poss(mid)) {
            hi = mid;
        }
        else lo = mid;
    }
    cout << hi << endl;
}

