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
  int N, K; cin >> N >> K;
  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    int p; cin >> p; p--;
    adj[p].push_back(i);
  }

  vector<ll> S(N);
  F0R(i, N) {
    cin >> S[i];
  }

  auto f = y_combinator([&](auto f, int i, int c) -> pair<ll, ll> {
    int d = sz(adj[i]);
    if (d == 0) {
      return {S[i] * c, S[i] * (c + 1)};
    }
    else {
      int take = c / d;
      int extra = c % d;

      vector<pair<ll, ll>> best;
      for (int j: adj[i]) {
        best.push_back(f(j, take));
      }
      sort(all(best), [](auto& a, auto& b) {
        return a.second - a.first > b.second - b.first;
          });

      pair<ll, ll> ans = {S[i] * c, S[i] * (c + 1)};
      for (int l = 0; l < sz(best); l++) {
        ans.first += l < extra ? best[l].second : best[l].first;
        ans.second += l < extra+1 ? best[l].second : best[l].first;
      }
      return ans;
    }
  });

  ll ans = f(0, K).first;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
