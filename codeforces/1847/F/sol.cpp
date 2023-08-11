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
  int N, Q; cin >> N >> Q;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];

  vector<vector<pair<int, int>>> changes(N); // round, val
  vector<vector<pair<int, int>>> U(N);
  F0R(k, 30) {
    vector<int> V(2*N);
    F0R(i, N) {
      V[i] = V[i + N] = (A[i] >> k) & 1;
    }
    if (std::accumulate(all(V), 0) == 0) continue;
    else {
      int cur = 0;
      F0Rd(i, 2*N) {
        if (V[i] == 1) cur = 0;
        else cur++;
        if (i < N) {
          if (i == N-1 && cur > 1) cur--;
          U[i].push_back({cur, k});
        }
      }
    }
  }
  F0R(i, N) {
    auto v = U[i];
    sort(all(v));
    int x = 0;
    F0R(j, sz(v)) {
      x |= 1 << v[j].second;
      if (j + 1 == sz(v) || v[j].first != v[j+1].first) {
        changes[i].push_back({v[j].first, x});
      }
    }
  }

  vector<ll> ans(Q, -1);
  vector<pair<int, int>> queries;
  F0R(i, Q) {
    int v; cin >> v;
    queries.push_back({v, i});
  }
  sort(all(queries));

  vector<pair<ll, int>> V;
  F0R(i, N) {
    for (auto [round, x] : changes[i]) {
      V.push_back({1LL * N * round + i + 1, x});
    }
  }
  sort(all(V));
  vector<pair<ll, int>> vec;
  for (auto [r, x]: V) {
    if (vec.empty() || vec.back().second < x) {
      vec.push_back({r, x});
    }
  }

  int j = 0;
  for (auto [v, id]: queries) {
    while (j < sz(vec) && vec[j].second <= v) j++;
    if (j < sz(vec)) {
      ans[id] = vec[j].first;
    }
  }

  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
