#include <bits/stdc++.h>
using namespace std;

// Template {{{
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define sz(x) (int)(x).size()

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
// }}}

int modpow(int a, int b, int mod) {
  int r = 1;
  while (b) {
    if (b&1) r = (1LL * r * a) % mod;
    a = (1LL * a * a) % mod;
    b >>= 1;
  }
  return r;
}

void solve() {
  int N, K; cin >> N >> K;
  using vi = vector<int>;
  vi A(N);
  F0R(i, N) cin >> A[i], --A[i];
  map<int, vector<vi>> cycles;
  vi vis(N);
  auto dfs = y_combinator([&](auto dfs, int i, vi& v) -> void {
    if (!vis[i]) {
      vis[i] = 1;
      v.push_back(i);
      dfs(A[i], v);
    }
  });
  F0R(i, N) if (!vis[i]) {
    vi cyc;
    dfs(i, cyc);
    cycles[sz(cyc)].push_back(cyc);
  }
  vector<vi> mcyc;
  int added = 0;
  for (int c = N; c >= 1; c--) {
    int m = __gcd(c, modpow(2, K, c));
    int l = c / m;
    int off = modpow(2, K, c);
    while (sz(cycles[l]) >= m) {
      vi v(c);
      F0R(i, m) {
        auto& u = cycles[l].back();
        F0R(j, l) {
          v[(i + 1LL * off * j) % c] = u[j];
          added++;
        }
        cycles[l].pop_back();
      }
      mcyc.push_back(v);
    }
  }

  if (added < N) {
    cout << "NO\n";
  }
  else {
    vector<int> ans(N);
    for (auto v: mcyc) {
      F0R(i, sz(v)) {
        int j = (i + 1) % sz(v);
        ans[v[i]] = v[j];
      }
    }
    cout << "YES\n";
    F0R(i, N) cout << ans[i]+1 << " \n"[i == N-1];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
