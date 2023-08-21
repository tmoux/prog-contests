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
  vector<pair<int, int>> top;
  DSU(int _n) {
    n = _n;
    par.resize(n, -1);
    top.resize(n);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    // keep y's top
    if (par[x] > par[y]) swap(x, y);
    else top[x] = top[y];
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  pair<int, int> getTop(int i) { // vertex, edge
    return top[Find(i)];
  }

  int compSize(int i) {
    return -par[Find(i)];
  }
};

const int maxn = 5e5+5, maxk = 20;
int N, K, M;

struct Forest {
  private:
    vector<vector<pair<int, int>>> adj;
    vector<int> depth;
    int redEdges;
    vector<vector<int>> par;
    DSU dsu, nextRed;
    vector<bool> isAssigned;

    int lca(int a, int b) {
      if (depth[a] > depth[b]) swap(a, b);
      for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (bb != -1 && depth[bb] >= depth[a]) b = bb;
      }
      if (a == b) return a;
      for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
          a = aa;
          b = bb;
        }
      }
      return par[0][a];
    }

    void rebuild(int i, int p, int e) {
      dsu.Union(i, p);
      // e is previous edge, or -1 if black edge/not exist
      nextRed.par[i] = -1;
      nextRed.top[i] = {i, e};
      if (e == -1 || isAssigned[e]) {
        nextRed.Union(i, p);
      }
      depth[i] = depth[p] + 1;
      par[0][i] = p;
      for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
      }
      for (auto [j, id]: adj[i]) {
        if (j == p) continue;
        rebuild(j, i, id);
      }
    }

    int removePathLCA(int a, int lc) {
      int ans = 0;
      while (nextRed.getTop(a) != nextRed.getTop(lc)) {
        auto [t, e] = nextRed.getTop(a);
        isAssigned[e] = 1;
        nextRed.Union(t, par[0][t]);
        ans++;
        redEdges--;
      }
      return ans;
    }

    bool isConnected(int a, int b) {
      return dsu.Find(a) == dsu.Find(b);
    }

    ll removePath(int a, int b, int w) {
      int lc = lca(a, b);
      ll ans = 0;
      ans += 1LL * w * removePathLCA(a, lc);
      ans += 1LL * w * removePathLCA(b, lc);
      return ans;
    }

    void join(int a, int b) {
      assert(!isConnected(a, b));
      if (dsu.compSize(a) < dsu.compSize(b)) swap(a, b);
      adj[a].emplace_back(b, -1);
      adj[b].emplace_back(a, -1);
      rebuild(b, a, -1);
    }

  public:
    Forest(int n, vector<array<int, 2>> reds) :
      adj(n),
      depth(n, -1),
      redEdges(sz(reds)),
      par(maxk, vector<int>(n, -1)),
      dsu(n),
      nextRed(n),
      isAssigned(sz(reds), false)
    {
      F0R(i, sz(reds)) {
        auto [a, b] = reds[i];
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
      }
      F0R(i, n) {
        if (depth[i] == -1) rebuild(i, i, -1);
      }
    }


    int getRedEdges() const {
      return redEdges;
    }

    ll process(int a, int b, int w) {
      if (isConnected(a, b)) return removePath(a, b, w);
      else {
        join(a, b);
        return 0;
      }
    }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K >> M;
  vector<array<int, 2>> reds;
  REP(K) {
    int a, b; cin >> a >> b;
    a--, b--;
    reds.push_back({a, b});
  }
  Forest f(N, reds);

  ll ans = 0;
  REP(M) {
    int a, b, w; cin >> a >> b >> w;
    a--, b--;
    ans += f.process(a, b, w);
  }
  cout << (f.getRedEdges() > 0 ? -1 : ans) << '\n';
}
