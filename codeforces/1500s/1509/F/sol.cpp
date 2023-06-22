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

const int maxn = 2e5+5;
int N, M;
vector<array<int, 2>> adj[maxn];

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  int X = 0;
  vector<array<int, 3>> edges;
  REP(M) {
    int a, b, w; cin >> a >> b >> w;
    edges.push_back({w, a, b});
    X ^= w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }
  sort(all(edges));
  if (N > 1000) {
    DSU dsu(N);
    set<int> S;
    FOR(i, 1, N+1) S.insert(i);
    FOR(i, 1, N+1) {
      sort(all(adj[i]));
      vector<int> v;
      for (auto [j, _]: adj[i]) {
        v.push_back(j);
      }
      v.push_back(N+1);
      int prev = 0;
      // cout << i << ": " << v << endl;
      // cout << S << endl;
      for (auto j: v) {
        if (prev+1 <= j-1) {
          vector<int> del;
          for (auto it = S.lower_bound(prev+1); it != S.end() && *it < j; ++it) {
            // cout << "adding edge " << *it << ' ' << i << endl;
            dsu.Union(*it, i);
            del.push_back(*it);
          }
          F0R(idx, sz(del)-1) {
            S.erase(del[idx]);
          }
        }
        prev = j;
      }
    }
    ll ans = 0;
    for (auto [w, a, b]: edges) {
      if (dsu.Union(a, b)) {
        ans += w;
      }
    }
    cout << ans << '\n';
  }
  else {
    vector<vector<int>> wt(N+1, vector<int>(N+1, 0));
    for (auto [w, a, b]: edges) {
      wt[a][b] = wt[b][a] = w;
    }

    bool has_cyc = false;
    DSU dsu(N);
    FOR(i, 1, N+1) {
      FOR(j, i+1, N+1) {
        if (wt[i][j] == 0) {
          if (!dsu.Union(i, j)) {
            has_cyc = true;
          }
        }
      }
    }

    if (has_cyc) {
      vector<array<int, 3>> es;
      FOR(i, 1, N+1) {
        FOR(j, i+1, N+1) {
          es.push_back({wt[i][j], i, j});
        }
      }
      dsu = DSU(N);
      sort(all(es));
      ll ans = 0;
      for (auto [w, a, b]: es) {
        if (dsu.Union(a, b)) {
          ans += w;
        }
      }
      cout << ans << '\n';
    }
    else {
      int mn = X;
      vector<int> bad(sz(edges));
      dsu = DSU(N);
      F0R(i, sz(edges)) {
        auto [w, a, b] = edges[i];
        if (!dsu.Union(a, b)) {
          bad[i] = true;
        }
      }

      dsu = DSU(N);
      FOR(i, 1, N+1) {
        FOR(j, i+1, N+1) {
          if (wt[i][j] == 0) {
            dsu.Union(i, j);
          }
        }
      }

      ll ans = 0;
      F0R(i, sz(edges)) {
        if (bad[i]) continue;
        else {
          auto [w, a, b] = edges[i];
          if (dsu.Union(a, b)) {
            ans += w;
          }
          else ckmin(mn, w);
        }
      }
      cout << ans + mn << '\n';
    }
  }
}
