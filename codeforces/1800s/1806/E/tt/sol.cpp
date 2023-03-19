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

const int maxn = 1e5+5;
ll A[maxn];

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<int> tonode;
  vector<ll> dp;

  void dfs(int i, int p, int& t) {
    dp[i] = A[i] * A[i];
    if (i != p) dp[i] += dp[p];
    tonode[t] = i;
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
      dfs(j, i, t);
    }
    tonode[t] = i;
    tout[i] = t++;
  }

  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    tin.resize(sz);
    tout.resize(sz);
    tonode.resize(2*sz);
    dp.resize(sz);
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    int t = 0;
    dfs(root, root, t);
  }

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

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }
};

struct Query
{
  int bucket, l, r, id;

  bool operator<(const Query& rhs) const {
    if (bucket != rhs.bucket) {
      return bucket < rhs.bucket;
    }
    else return r < rhs.r;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  F0R(i, N) cin >> A[i];

  Tree tree(N);
  FOR(i, 1, N) {
    int p; cin >> p; p--;
    tree.add_edge(p, i);
  }
  tree.init();


  int size = (int)(sqrt(Q) + 1);
  vector<Query> queries;
  vector<ll> ans(Q);
  F0R(i, Q) {
    int x, y; cin >> x >> y;
    x--, y--;

    if (x == y) {
      ans[i] = tree.dp[x];
    }
    else {
      int lca = tree.lca(x, y);
      ans[i] = tree.dp[lca];

      if (tree.tin[x] > tree.tout[y]) swap(x, y);
      int l = tree.tout[x], r = tree.tin[y];

      queries.push_back({l / size, l, r, i});
    }
  }
  sort(all(queries));

  {
    ll total = 0;
    vector<int> freq(N, 0);
    vector<ll> sums(N+1, 1);
    vector<int> cnt(N+1, 0);
    auto contr = [&](int d) -> ll {
      return cnt[d] == 2 ? sums[d] : 0;
    };
    auto update = [&](int x, int d) -> void {
      int i = tree.tonode[x];
      freq[i] += d;
      // assert(0 <= freq[i] && freq[i] <= 2);
      int depth = tree.depth[i];

      total -= contr(depth);
      if (freq[i] == 1) {
        cnt[depth]++;
        sums[depth] *= A[i];
      }
      else {
        cnt[depth]--;
        // assert(sums[depth] % A[i] == 0);
        sums[depth] /= A[i];
      }
      total += contr(depth);
    };
    int L = 0, R = 0;
    for (Query q: queries) {
      while (R <= q.r) {
        update(R, 1);
        R++;
      }

      while (R > q.r + 1) {
        update(R-1, -1);
        R--;
      }

      while (L <= q.l) {
        update(L, -1);
        L++;
      }

      while (L > q.l) {
        update(L-1, 1);
        L--;
      }

      ans[q.id] += total;
    }
  }

  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}
