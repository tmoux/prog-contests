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

struct DSU {
  int n;
  vector<int> par;
  DSU() {}
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  bool connected(int x, int y) {
    return Find(x) == Find(y);
  }
};

const int maxn = 1e5+5;
int N, M;
vector<pair<int, int>> adj[maxn];

DSU dsus[30];
bool can[maxn]; // can be 1
bool isborder[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }

  F0R(k, 30) {
    dsus[k] = DSU(N+1);
    FOR(i, 1, N+1) {
      for (auto [j, w]: adj[i]) {
        if (w & (1 << k)) {
          dsus[k].Union(i, j);
        }
      }
    }
  }

  vector<vector<int>> comps(N+1);
  FOR(i, 1, N+1) {
    int c = dsus[0].Find(i);
    comps[c].push_back(i);
    for (auto [j, _]: adj[i]) {
      if (!dsus[0].connected(i, j)) isborder[i] = true;
    }
  }

  vector<bool> vis(N+1, false);
  vector<bool> incomp(N+1, false);
  for (auto v: comps) {
    for (auto i: v) incomp[i] = 1;
    if (!v.empty()) {
      // cout << "Comp " << v << endl;
      FOR(k, 1, 30) {
        auto dfs = y_combinator([&](auto dfs, int i, vector<int>& C, bool& b) -> void {
          vis[i] = 1;
          if (isborder[i]) b = true;
          C.push_back(i);
          for (auto [j, w]: adj[i]) {
            if (incomp[j] && w & (1 << k) && !vis[j]) {
              dfs(j, C, b);
            }
          }
        });
        for (auto i: v) {
          if (!vis[i]) {
            vector<int> C;
            bool has_border = false;
            dfs(i, C, has_border);
            if (has_border) {
              for (auto j: C) {
                can[j] = true;
              }
            }
          }
        }
        // reset vis
        for (auto i: v) vis[i] = 0;
      }
    }
    for (auto i: v) incomp[i] = 0;
  }
  // FOR(i, 1, N+1) {
  //   cout << i << ": " << can[i] << endl;
  // }

  int Q; cin >> Q;
  while (Q--) {
    int u, v; cin >> u >> v;
    int ans = -1;
    F0R(i, 30) {
      if (dsus[i].connected(u, v)) {
        ans = 0;
        break;
      }
    }
    if (ans == -1) {
      ans = can[u] ? 1 : 2;
    }
    cout << ans << '\n';
  }
}
