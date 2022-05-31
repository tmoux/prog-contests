#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
  template <class Fun>
    class y_combinator_result {
      Fun fun_;

      public:
      template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

      template <class... Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template <class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
!is_same<T_container, string>::value,
  typename T_container::value_type>::type>
  ostream &operator<<(ostream &os, const T_container &v) {
    os << '[';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << ']';
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    string s; cin >> s;

    auto get_pref = [&](string s) -> vector<int> {
      vector<int> pref(sz(s)+1, 0);
      F0R(i, sz(s)) {
        pref[i+1] = (s[i] == '(' ? 1 : -1) + (i == 0 ? 0 : pref[i]);
      }
      return pref;
    };

    vector<int> pref = get_pref(s);
    if (*min_element(all(pref)) == 0) {
      cout << 0 << '\n';
    }
    else {
      auto max_index = [&](int l, int r) -> int {
        pair<int, int> ans = {-1, -1};
        for (int i = l; i <= r; i++) {
          ckmax(ans, {pref[i+1], i});
        }
        return ans.second;
      };

      auto flip_range = [&](int l, int r) -> string {
        string rev = s.substr(l, r-l+1);
        reverse(all(rev));
        return s.substr(0, l) + rev + s.substr(r+1);
      };

      int L = 0;
      while (pref[L] >= 0) L++;
      int R = 2*n;
      while (pref[R] >= 0) R--;

      // cout << pref << endl;
      // cout << L << ' ' << R << endl;

      int i = 0;
      for (int k = 0; k < L; k++) {
        if (pref[k] >= pref[i]) i = k;
      }
      int j = 2*n;
      for (int k = 2*n; k > R; k--) {
        if (pref[k] >= pref[j]) j = k;
      }

      auto ns = flip_range(i, j-1);
      auto pref1 = get_pref(ns);
      // cout << ns << endl;
      // cout << pref1 << endl;
      if (*min_element(all(pref1)) == 0) {
        cout << 1 << '\n';
        cout << i+1 << ' ' << j << '\n';
      }
      else {
        i = max_index(0, 2*n-1);
        cout << 2 << '\n';
        cout << 1 << ' ' << i+1 << '\n';
        cout << i+2 << ' ' << 2*n << '\n';
      }
    }
  }
}
