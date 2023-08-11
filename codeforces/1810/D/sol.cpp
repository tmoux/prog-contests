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

void solve() {
  int Q; cin >> Q;
  ll L = 0, R = 2e18;

  auto getn = [&](ll h, ll a, ll b) -> ll {
    if (h <= a) return 1;
    ll n = (h - a) / (a - b);
    ll cur = n * (a - b);
    while (true) {
      n++;
      cur += a;
      if (cur >= h) return n;
      cur -= b;
    }
    assert(false);
  };

  while (Q--) {
    int t; cin >> t;
    ll a, b; cin >> a >> b;
    if (t == 1) {
      ll n; cin >> n;
      ll LL, RR;
      if (n == 1) {
        LL = 0;
        RR = a;
      }
      else {
        LL = (n - 2) * (a - b) + a;
        RR = (n - 1) * (a - b) + a;
      }

      if (max(L, LL) < min(R, RR)) {
        ckmax(L, LL);
        ckmin(R, RR);
        cout << 1 << ' ';
      }
      else cout << 0 << ' ';
    }
    else {
      ll n1 = getn(L+1, a, b);
      ll n2 = getn(R, a, b);
      if (n1 == n2) {
        cout << n1 << ' ';
      }
      else {
        cout << -1 << ' ';
      }
    }
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
