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

ll solve() {
  ll B, K; cin >> B >> K;
  using pii = pair<ll, ll>;
  pii S; cin >> S.first >> S.second;
  pii G; cin >> G.first >> G.second;

  auto dist = [](pii a, pii b) -> ll {
    return abs(a.first - b.first) + abs(a.second - b.second);
  };

  ll ans = K * dist(S, G);

  {
    ll nx = (S.first/B)*B;
    ll ny = (S.second/B)*B;

    for (auto nnx: {nx, nx+B}) {
      ckmin(ans, K * (abs(S.first - nnx) + abs(nnx - G.first)) + abs(S.second - G.second));
      ckmin(ans, K * (abs(S.first - nnx) + abs(nnx - G.first)) + abs(S.second - G.second));
    }
    for (auto nny: {ny, ny+B}) {
      ckmin(ans, K * (abs(S.second - nny) + abs(nny - G.second)) + abs(S.first - G.first));
      ckmin(ans, K * (abs(S.second - nny) + abs(nny - G.second)) + abs(S.first - G.first));
    }
  }

  vector<pair<pii, ll>> vs, vg;
  vector<pair<pii&, vector<pair<pii, ll>>&>> vec = {{S, vs}, {G, vg}};
  for (auto& [p, v]: vec) {
    auto [x, y] = p;
    ll nx = (x/B)*B;
    ll ny = (y/B)*B;

    for (auto nnx: {nx, nx+B}) {
      for (auto nny: {ny, ny+B}) {
        v.push_back({{nnx, nny}, K * abs(x - nnx) + abs(y - nny)});
        v.push_back({{nnx, nny}, abs(x - nnx) + K * abs(y - nny)});
      }
    }
  }

  for (auto [p1, d1]: vs) {
    for (auto [p2, d2]: vg) {
      ll tr = (d1 + d2) + dist(p1, p2);
      ckmin(ans, tr);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
