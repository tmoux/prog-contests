#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

// }}}

ll solve() {
  string s; cin >> s;
  int n = sz(s);
  vector<int> paren(n);
  vector<int> closing;
  for (int i = 0; i < n; i++) {
    int prev = i == 0 ? 0 : paren[i-1];
    paren[i] = s[i] == '(' ? prev + 1 : prev - 1;
    assert(paren[i] >= 0);

    if (s[i] == ')') {
      closing.push_back(i);
    }
  }

  int m = sz(closing);
  vector<ll> pref(m);
  for (int i = 0; i < m; i++) {
    pref[i] = closing[i];
    if (i > 0) pref[i] += pref[i-1];
  }
  const ll INF = 2e18;
  auto getcost = [&](int i, int k) {
    int l = distance(closing.begin(), lower_bound(all(closing),i));
    if (l + k - 1 < m) {
      int r = l+k-1;
      ll cost = pref[r] - (l == 0 ? 0 : pref[l-1]);
      ll sub = (ll)(i + (i+k-1)) * (ll)k / 2;
      cost -= sub;
      return cost;
    }
    else return INF;
  };

  ll ans = INF;
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      //cout << i << ": " << getcost(i, paren[i]) << endl;
      ckmin(ans, getcost(i, paren[i]));
    }
  }
  assert(ans < INF);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
