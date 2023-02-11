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

ll Pow(ll a, ll b) {
  ll res = 1;
  REP(b) res *= a;
  return res;
}

int brute(int N, int M) {
  set<ll> s;
  FOR(i, 1, N+1) {
    FOR(j, 1, M+1) {
      s.insert(Pow(i, j));
      // cout << Pow(i, j) << ' ';
    }
    cout << '\n';
    cout << i << ": " << sz(s) << endl;
  }
  cout << '\n';
  return sz(s);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  // cout << brute(N, M) << '\n';
  const int MX = 22;
  vector<bool> seen(MX * M);
  vector<int> distinct(MX+1);
  int d = 0;
  for (int i = 1; i < MX; i++) {
    for (int j = 1; j <= M; j++) {
      if (!seen[i*j-1]) {
        d++;
        seen[i*j-1] = 1;
      }
    }
    distinct[i] = d;
  }
  auto g = [&](int l) -> int {
    assert(l < MX);
    return distinct[l];
  };
  ll ans = 1;
  vector<bool> ok(N+1, true);
  for (int i = 2; i <= N; i++) {
    if (!ok[i]) continue;
    int l = 0;
    for (ll x = i; x <= N; x *= i) {
      ok[x] = false;
      l++;
    }
    ans += g(l);
  }

  cout << ans << '\n';
}
