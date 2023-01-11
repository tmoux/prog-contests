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

using vi = vector<int>;
using pii = pair<int, int>;

namespace BC {
  vi num, st;
  vector<vector<pii>> ed;
  vector<pii> edges, bridges;
  int Time;
  template<class F>
  int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
          top = min(top, num[y]);
          if (num[y] < me)
            st.push_back(e);
        } else {
          int si = sz(st);
          int up = dfs(y, e, f);
          top = min(top, up);
          if (up == me) {
            st.push_back(e);
            f(vi(st.begin() + si, st.end()));
            st.resize(si);
          }
          else if (up < me) st.push_back(e);
          else {
            auto [a, b] = edges[e];
            bridges.emplace_back(a, b);
          }
        }
      }
    return top;
  }

  template<class F>
  void bicomps(F f) {
    num.assign(sz(ed), 0);
    FOR(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
  }
} using namespace BC;

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<int> sum;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
      sum[j] += sum[i];
      dfs(j, i, t);
    }
    tout[i] = t-1;
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
    sum.resize(sz);
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init(int root) {
    int t = 0;
    dfs(root, -1, t);
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

  bool is_ancestor(int lca, int a) {
    return tin[lca] <= tin[a] && tin[a] <= tout[lca];
  }

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }

  int path_sum(int a, int b) {
    int l = lca(a, b);
    return sum[a] + sum[b] - sum[l] - (par[0][l] == -1 ? 0 : sum[par[0][l]]);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  ed.resize(N);
  int eid = 0;
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    edges.push_back({a, b});
    ed[a].emplace_back(b, eid);
    ed[b].emplace_back(a, eid++);
  }

  Tree tree(2 * N);
  vi comp_size(2 * N);
  int new_node = N;
  bicomps([&](const vi& edgelist) {
    vi v;
    for (int e: edgelist) {
      auto [a, b] = edges[e];
      v.push_back(a);
      v.push_back(b);
    }
    sort(all(v)); v.erase(unique(all(v)), v.end());
    comp_size[new_node] = sz(edgelist);
    for (int i: v) {
      tree.add_edge(i, new_node);
    }
    new_node++;
  });
  tree.sum = comp_size;

  for (auto [a, b]: bridges) {
    tree.add_edge(a, b);
  }
  tree.init(0);

  int Q; cin >> Q;
  while (Q--) {
    int a, b; cin >> a >> b;
    a--, b--;
    cout << tree.path_sum(a, b) << '\n';
  }
}
