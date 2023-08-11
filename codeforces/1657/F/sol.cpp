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

namespace twosat {
  int n;
  vector<vector<int>> adj, adj_t;
  vector<bool> used;
  vector<int> order, comp;
  vector<bool> assignment;

  void dfs1(int v) {
    used[v] = true;
    for (int u : adj[v]) {
      if (!used[u])
        dfs1(u);
    }
    order.push_back(v);
  }

  void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : adj_t[v]) {
      if (comp[u] == -1)
        dfs2(u, cl);
    }
  }

  bool solve_2SAT() {
    order.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
      if (!used[i])
        dfs1(i);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
      int v = order[n - i - 1];
      if (comp[v] == -1)
        dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
      if (comp[i] == comp[i + 1])
        return false;
      assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
  }

  void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
  }
}
using twosat::add_disjunction;

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
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
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
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

  vector<int> getpath(int a, int b) {
    int lc = lca(a, b);
    vector<int> va, vb;
    while (depth[a] >= depth[lc]) {
      va.push_back(a);
      a = par[0][a];
    }
    while (depth[b] > depth[lc]) {
      vb.push_back(b);
      b = par[0][b];
    }
    reverse(all(vb));
    for (auto x: vb) va.push_back(x);
    return va;
  }
};

void fail() {
  cout << "NO" << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  Tree tree(N);
  vector<bool> touch(N, false);
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    tree.add_edge(a, b);
  }
  tree.init();
  vector<vector<char>> C(N);
  vector<vector<pair<int, int>>> ids(N);
  struct Query {
    int x, y;
    string s;
  };
  vector<Query> queries(Q);
  F0R(i, Q) {
    int x, y; string s; cin >> x >> y >> s;
    x--, y--;
    queries[i] = {x, y, s};

    auto path = tree.getpath(x, y);
    // cout << s << ' ' << path << endl;
    assert(sz(path) == sz(s));
    F0R(idx, sz(path)) {
      vector<char> v;
      v.push_back(s[idx]);
      v.push_back(s[sz(s)-1-idx]);
      sort(all(v)); v.erase(unique(all(v)), v.end());
      int z = path[idx];
      ids[z].push_back({i, idx});
      if (!touch[z]) {
        touch[z] = 1;
        C[z] = v;
      }
      else {
        vector<char> nv;
        for (auto c: C[z]) {
          if (find(all(v), c) != v.end()) {
            nv.push_back(c);
          }
        }
        C[z] = nv;
      }
    }
  }

  int VARS = N + Q;
  twosat::n = 2 * VARS;
  twosat::adj.resize(twosat::n);
  twosat::adj_t.resize(twosat::n);
  F0R(i, N) {
    if (touch[i]) {
      // cout << i << ": " << C[i] << ' ' << ids[i] << endl;
      if (C[i].empty()) fail();
      else if (sz(C[i]) == 1) {
        char c = C[i][0];
        add_disjunction(i, false, i, false); // i is true
        for (auto [j, idx]: ids[i]) {
          char a = queries[j].s[idx];
          char b = queries[j].s[sz(queries[j].s)-1-idx];
          if (c == a && c == b) {
            // say nothing
          }
          else if (c == a) {
            add_disjunction(i, true, N + j, false);
          }
          else if (c == b) {
            add_disjunction(i, true, N + j, true);
          }
          else fail();
        }
      }
      else if (sz(C[i]) == 2) {
        char c = C[i][0];
        char d = C[i][1];
        assert(c != d);
        for (auto [j, idx]: ids[i]) {
          char a = queries[j].s[idx];
          char b = queries[j].s[sz(queries[j].s)-1-idx];
          if (a == b) {
            if (c == a) {
              // i is true
              add_disjunction(i, false, i, false);
            }
            else if (d == a) {
              // i is false
              add_disjunction(i, true, i, true);
            }
            else fail();
          }
          else if (c == a && d == b) {
            add_disjunction(i, true, N + j, false);
            add_disjunction(N + j, true, i, false);
          }
          else if (c == b && d == a) {
            add_disjunction(i, false, N + j, false);
            add_disjunction(N + j, true, i, true);
          }
          else if (c == a) {
            // i is true, and implies j is true
            add_disjunction(i, false, i, false);
            add_disjunction(i, true, j, false);
          }
          else if (c == b) {
            add_disjunction(i, false, i, false);
            add_disjunction(i, true, j, true);
          }
          else if (d == a) {
            // i is false, and implies j is true
            add_disjunction(i, true, i, true);
            add_disjunction(i, false, j, false);
          }
          else if (d == b) {
            add_disjunction(i, true, i, true);
            add_disjunction(i, false, j, true);
          }
          else fail();
        }
      }
      else assert(false);
    }
  }

  bool poss = twosat::solve_2SAT();
  if (!poss) fail();
  else {
    cout << "YES\n";
    F0R(i, N) {
      if (!touch[i]) cout << 'z';
      else if (twosat::assignment[i]) cout << C[i][0];
      else cout << C[i][1];
    }
    cout << '\n';
  }
}
