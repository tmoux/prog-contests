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

vector<int> get_divs(int x) {
  vector<int> v;
  for (int i = 1; i*i <= x; i++) {
    if (x % i == 0) {
      v.push_back(i);
      if (x/i > i) v.push_back(x/i);
    }
  }
  sort(all(v));
  return v;
}

void solve() {
  int N, M1, M2; cin >> N >> M1 >> M2;
  ll M = 1LL * M1 * M2;
  auto d1 = get_divs(M1);
  auto d2 = get_divs(M2);
  vector<ll> divs;
  for (auto x: d1) for (auto y: d2) {
    if (M % (1LL*x*y) == 0) {
      divs.push_back(1LL*x*y);
    }
  }
  sort(all(divs)); divs.erase(unique(all(divs)), divs.end());

  int cnt = 0, ans = 0;
  for (ll d: divs) {
    ll t = (d + N - 1) / N;
    for (auto it = lower_bound(all(divs), t); it != divs.end() && *it <= N; ++it) {
      if (d % *it == 0) {
        cnt++;
        ans ^= *it;
        break;
      }
    }
  }
  cout << cnt << ' ' << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
