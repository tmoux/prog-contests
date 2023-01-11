#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

using vi = vector<int>;
bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a]) if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    /// Find the starting nodes for BFS (i.e. layer 0).
    cur.clear();
    for (int a : btoa) if(a != -1) A[a] = -1;
    FOR(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
    /// Find all layers using bfs.
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur) for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          }
          else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    /// Use DFS to scan for augmenting paths.
    FOR(a,0,sz(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}

std::optional<tuple<int, int, vi>> solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  F0R(i, N) {
    cin >> A[i];
  }
  map<int, vi> toIndices;
  F0R(i, N) {
    cin >> B[i];
    toIndices[B[i]].push_back(i);
  }

  auto check = [&](int p1, int p2, const vector<int>& btoa) -> tuple<int, int, vi> {
    vector<int> atob(N);
    F0R(j, N) atob[btoa[j]] = j;
    vector<int> X(N);
    F0R(j, N) {
      int d = A[j];
      int idx = atob[j];
      if (B[idx] == abs(p2 - (p1 + d))) {
        X[j] = -A[0] + d;
      }
      else {
        assert(B[idx] == abs(p2 - (p1 - d)));
        X[j] = -A[0] - d;
      }
    }
    int min_x = min({p1, p2, *min_element(all(X))});
    F0R(j, N) X[j] -= min_x;
    p1 -= min_x, p2 -= min_x;
    if (max({*max_element(all(X)), p1, p2}) <= 2000000000) {
      return {p1, p2, X};
    }
    else return {-1, -1, {}};
  };
  F0R(i, N) {
    // try p1 = -A[0], p2 = B[i]
    {
      vector<vi> g(N);
      F0R(j, N) {
        int d = A[j];
        int e1 = abs(B[i] - (-A[0] + d));
        int e2 = abs(B[i] - (-A[0] - d));
        for (int idx: toIndices[e1]) g[j].push_back(idx);
        for (int idx: toIndices[e2]) g[j].push_back(idx);
      }
      vi btoa(N, -1);
      int s = hopcroftKarp(g, btoa);
      if (s == N) {
        auto c = check(-A[0], B[i], btoa);
        if (get<0>(c) != -1) return c;
      }
    }
    // try p1 = -A[0], p2 = -B[i]
    {
      vector<vi> g(N);
      F0R(j, N) {
        int d = A[j];
        int e1 = abs(-B[i] - (-A[0] + d));
        int e2 = abs(-B[i] - (-A[0] - d));
        for (int idx: toIndices[e1]) g[j].push_back(idx);
        for (int idx: toIndices[e2]) g[j].push_back(idx);
      }
      vi btoa(N, -1);
      int s = hopcroftKarp(g, btoa);
      if (s == N) {
        auto c = check(-A[0], -B[i], btoa);
        if (get<0>(c) != -1) return c;
      }
    }
  }

  return std::nullopt;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    auto c = solve();
    if (c) {
      cout << "YES" << '\n';
      auto [p1, p2, v] = *c;
      for (auto x: v) {
        cout << x << ' ';
      }
      cout << '\n';
      cout << p1 << ' ' << p2 << '\n';
    }
    else {
      cout << "NO" << '\n';
    }
  }
}
