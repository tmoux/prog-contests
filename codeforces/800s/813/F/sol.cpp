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

// DSU with rollbacks {{{
struct DSU {
  int SZ;
  vector<int> parent, sz, weight;
  stack<int> st;
  stack<bool> bipartite_state;

  DSU(int N) {
    SZ = N + 1;
    parent.resize(SZ); iota(all(parent), 0);
    sz.resize(SZ, 1);
    weight.resize(SZ, 0);
    bipartite_state.push(true);
  }

  int depth(int i) {
    if (parent[i] == i) {
      return 0;
    }
    else return weight[i] ^ depth(parent[i]);
  }

  // no path compression
  int Find(int i) {
    if (parent[i] == i) return i;
    else return Find(parent[i]);
  }

  void merge(int i, int j) {
    int ii = i, jj = j;
    i = Find(i);
    j = Find(j);

    if (i == j) {
      bool b = bipartite_state.top() && (depth(ii) != depth(jj));
      bipartite_state.push(b);
      st.push(-1);
    }
    else {
      if (sz[i] < sz[j]) swap(i, j);
      // Adjust weight (remember to adjust parent j's weight)
      weight[j] = depth(jj) ^ depth(ii) ^ 1;

      parent[j] = i;
      sz[i] += sz[j];

      bipartite_state.push(bipartite_state.top());
      st.push(j);
    }
  }

  bool is_bipartite() const {
    return bipartite_state.top();
  }

  void rollback() {
    assert(!st.empty());

    int j = st.top(); st.pop();
    if (j != -1) {
      int i = parent[j];
      sz[i] -= sz[j];
      parent[j] = j;
      weight[j] = 0;
    }

    bipartite_state.pop();
  }
}; // }}}

struct Node { // {{{
  int se, en;
  vector<pair<int, int>> edges;
};

struct SegmentTree { 
  vector<Node> nodes;
  DSU dsu;

  SegmentTree(int N, int Q) : dsu(DSU(N)) {
    nodes.resize(4*Q);
    build(1, 0, Q-1);
  }

  void build(int i, int se, int en) {
    nodes[i].se = se;
    nodes[i].en = en;
    if (se == en) return;
    int m = (se+en)>>1;
    build(i*2, se, m);
    build(i*2+1, m+1, en);
  }

  void addInterval(int i, int l, int r, pair<int, int> p) {
    if (l <= nodes[i].se && nodes[i].en <= r) {
      nodes[i].edges.push_back(p);
      return;
    }
    if (nodes[i].se == nodes[i].en) return;
    int mid = (nodes[i].se+nodes[i].en)>>1;
    if (mid >= l) addInterval(i*2, l, r, p);
    if (mid < r) addInterval(i*2+1, l, r, p);
  }

  void DFS(int i, vector<bool>& ans) {
    for (auto [x, y]: nodes[i].edges) {
      dsu.merge(x, y);
    }

    if (nodes[i].se == nodes[i].en) {
      ans[nodes[i].se] = dsu.is_bipartite();
    }
    else {
      DFS(i*2, ans);
      DFS(i*2+1, ans);
    }

    REP(sz(nodes[i].edges)) {
      dsu.rollback();
    }
  }
}; // }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q;
  cin >> N >> Q;

  SegmentTree segtree(N, Q);
  map<pair<int, int>, int> edges;
  for (int i = 0; i < Q; i++) {
    int x, y; cin >> x >> y;
    if (edges.count({x, y})) {
      int l = edges[{x, y}];
      int r = i-1;
      segtree.addInterval(1, l, r, {x, y});
      edges.erase({x, y});
    }
    else {
      edges[{x, y}] = i;
    }
  }
  for (auto [p, l]: edges) {
    auto [x, y] = p;
    segtree.addInterval(1, l, Q-1, {x, y});
  }

  vector<bool> ans(Q);
  segtree.DFS(1, ans);

  for (int i = 0; i < Q; i++) {
    cout << (ans[i] ? "YES" : "NO") << '\n';
  }
}
