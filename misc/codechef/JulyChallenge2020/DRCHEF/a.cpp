#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MX = 1e9;

int calc(int x, int y) {
    int res = 0;
    while (x < y) {
        y = min(y,2*(y-x));
        x *= 2;
        res++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int N;
        int x;
        cin >> N >> x;
        vector<int> a(N);
        multiset<int> s;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            s.insert(a[i]);
        }
        int ans = 0;
        while (!s.empty() && s.upper_bound(x) != s.end()) {
            ans++;
            int nsteps = calc(x,*s.rbegin());
            int lo = x/2, hi = x;
            while (lo + 1 < hi) {
                int mid = (lo+hi)/2;
                if (calc(mid,*s.rbegin()) == nsteps) {
                    hi = mid;
                }
                else {
                    lo = mid;
                }
            }
            int lbound = hi;
            auto it = s.upper_bound(x);
            if (it != s.begin() && lbound <= *prev(it)) {
                --it;
                x = (*it)*2;
                s.erase(it);
            }
            else {
                auto it = s.lower_bound
                auto it = s.rbegin();
                s.insert(min(*it,2*(*it-x)));
                s.erase(prev(s.end()));
                x *= 2;
            }
        }
        ans += s.size();
        cout << ans << '\n';
    }
}

