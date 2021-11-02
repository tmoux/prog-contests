#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;

    vector<int> even(n+1), odd(n+1);
    for (int i = 1; i <= n; i++) {
        if (s[i-1] == '+') {
            if (i % 2 == 1) odd[i]++;
            else even[i]++;
        }
        even[i] += even[i-1];
        odd[i] += odd[i-1];
    }
    vector<int> d(n+1);
    for (int i = 1; i <= n; i++) d[i] = odd[i] - even[i];

    auto sum_range = [&](int l, int r) {
        if (l > r) return 0;
        return d[r] - d[l-1];
    };

    map<int,set<int>> sumpos;
    for (int i = 1; i <= n; i++) {
        sumpos[d[i]+d[i-1]].insert(i);
    }

    function<vector<int>(int,int)> calc_ans;
    calc_ans = [&](int l, int r) -> vector<int> {
        if ((r-l+1) % 2 == 0 && sum_range(l, r) == 0) {
            return {};
        }
        else {
            //for (int i: {l, r}) {

            if ((r-l) % 2 == 0) {
                for (int i: {l, r}) {
                    if (sum_range(l, i-1) == sum_range(i+1, r)) {
                        return {i};
                    }
                }

                auto it = sumpos[d[l-1]+d[r]].upper_bound(l);
                if (it != sumpos[d[l-1]+d[r]].end() && l < *it && *it < r) {
                    //cout << "found it " << *it << '\n';
                    return {*it};
                }
            }

            auto ans = calc_ans(l+1, r);
            ans.push_back(l);
            return ans;
        }
    };

    while (q--) {
        int l, r; cin >> l >> r;
        auto ans = calc_ans(l, r);
        assert(ans.size() <= 2);
        cout << ans.size() << '\n';
        if (!ans.empty()) {
            for (auto i: ans) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int T; cin >> T;
  while (T--) solve();
}
