#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

// Make an edge for each array, and each number
// Draw an edge from each array to each number that appears in graph
// Each array node has even degree.
// Each number node has even degree if it's possible.
// Find an euler circuit, and label the edges alternating L, R, L, ...
// Since the graph is bipartite, for each array node, half of the edges will be L and half the edges will be R.
// Similarly for the number nodes.

namespace Euler {
  typedef vector<pair<int,int>> vpi;
  const int MX = 4e5+5;
  int N, M;
  vector<vpi> graph(MX); //{ed, edNum}
  vector<vpi::iterator> its(MX);
  vector<bool> used(MX);

  void init() {
    F0R(i, N) its[i] = begin(graph[i]);
    F0R(i, M) used[i] = false;
  }

  vpi eulerPath(int r) {
      // F0R(i, N) its[i] = begin(graph[i]);
      // F0R(i, M) used[i] = false;
      vpi ans, s{{r, -1}};
      int lst = -1;
      while (sz(s)) {
          int x = s.back().first; auto &it = its[x], en = end(graph[x]);
          while (it != en && used[it->second]) it++;

          if (it == en) {
              if (lst != -1 && lst != x) return {};
              ans.push_back(s.back()); s.pop_back(); if (sz(s)) lst = s.back().first;
          } else {
              s.push_back(*it);
              used[it->second] = 1;
          }
      }
      // if (sz(ans) != M+1) return {};
      return ans;
  }
};
using namespace Euler;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int m; cin >> m;
  int edge_idx = 0;
  int num_nodes = m;

  map<int,int> toIdx;
  auto add_edge = [&](int i, int x) {
    int idx = edge_idx++;
    if (!toIdx.count(x)) toIdx[x] = num_nodes++;
    x = toIdx[x];
    graph[i].push_back({x, idx});
    graph[x].push_back({i, idx});
  };
  map<int, pair<int,int>> toPos;
  vector<string> ans(m);
  F0R(i, m) {
    int n; cin >> n;
    ans[i].resize(n, '#');
    F0R(j, n) {
      int x; cin >> x;
      toPos[edge_idx] = {i, j};
      add_edge(i, x);
    }
  }
  N = num_nodes;
  M = edge_idx;

  assert(N < MX && M < MX);

  F0R(i, N) {
    if (sz(graph[i]) % 2 != 0) {
      cout << "NO\n";
      return 0;
    }
  }

  init();
  vector<bool> vis(N, false);
  F0R(i, N) {
    if (!vis[i]) {
      auto circuit = eulerPath(i);
      F0R(j, sz(circuit)) vis[circuit[j].first] = true;

      F0R(j, sz(circuit)-1) {
        auto [a, b] = toPos[circuit[j].second];
        ans[a][b] = j % 2 == 0 ? 'L' : 'R';
      }
    }
  }

  // output
  cout << "YES\n";
  F0R(i, sz(ans)) {
    cout << ans[i] << '\n';
  }
}
