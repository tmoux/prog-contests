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
  int N, M, P; cin >> N >> M >> P;
  vector<ll> W(N);
  F0R(i, N) {
    cin >> W[i];
  }
  vector<vector<pair<int, int>>> adj(N);
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    a--, b--;
    adj[a].push_back({b, w});
  }

  auto cv = [&](int i, int j) {
    return i * N + j;
  };
  auto ceil = [](ll a, ll b) -> ll {
    return (a + b - 1) / b;
  };

  using T = pair<ll, ll>;
  using U = pair<T, int>;
  vector<T> dist(N*N, {1e18, 1e18});

  priority_queue<U, vector<U>, greater<U>> pq;
  dist[cv(0, 0)] = {0, -P};
  pq.push({dist[cv(0, 0)], cv(0, 0)});

  while (!pq.empty()) {
    auto [q, I] = pq.top(); pq.pop();
    auto [d, p] = q;
    int i = I / N, ii = I % N;
    p = -p;
    for (auto [j, s]: adj[i]) {
      ll days = s <= p ? 0 : ceil(s - p, W[ii]);
      ll np = p + W[ii] * days - s;
      int nii = W[j] > W[ii] ? j : ii;

      T cost = {d + days, -np};
      if (dist[cv(j, nii)] > cost) {
        dist[cv(j, nii)] = cost;
        pq.push({dist[cv(j, nii)], cv(j, nii)});
      }
    }
  }

  ll ans = 1e18;
  F0R(i, N) {
    ckmin(ans, dist[cv(N-1, i)].first);
  }
  cout << (ans < 1e18 ? ans : -1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
