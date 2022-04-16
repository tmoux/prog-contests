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

vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, component;

void dfs1 (int v) {
  used[v] = true;
  for (size_t i=0; i<g[v].size(); ++i)
    if (!used[g[v][i]])
      dfs1(g[v][i]);
  order.push_back(v);
}

void dfs2 (int v) {
  used[v] = true;
  component.push_back(v);
  for (size_t i=0; i<gr[v].size(); ++i)
    if (!used[gr[v][i]])
      dfs2(gr[v][i]);
}

ll solve() {
  int n, m; cin >> n >> m;

  g = vector<vector<int>>(n);
  gr = vector<vector<int>>(n);
  used = vector<bool>(n, false);
  order.clear();
  component.clear();

  F0R(i, m) {
    int u, v; cin >> u >> v; 
    u--; v--;
    g[u].push_back(v);
    gr[v].push_back(u);
  }
  // Condense graph{{{
  for (int i=0; i<n; ++i)
    if (!used[i])
      dfs1(i);
  used.assign(n, false);

  vector<int> comp(n, -1);
  vector<int> comp_size;
  int c = 0;
  for (int i=0; i<n; ++i) {
    int v = order[n-1-i];
    if (!used[v]) {
      dfs2(v);

      comp_size.push_back(sz(component));
      for (auto x: component) {
        comp[x] = c;
      }
      component.clear();
      c++;
    }
  } /*}}}*/

  set<pair<int,int>> edges; // edges in condensation graph
  vector<vector<int>> adj(c); // Adjcency list of condensed graph (undirected)
  vector<vector<int>> rev(c);

  // Construct graph{{{
  F0R(i, n) {
    int a = comp[i];
    for (int j: g[i]) {
      int b = comp[j];
      if (a != b) edges.insert({a, b});
    }
  }
  for (auto [u, v]: edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    rev[v].push_back(u);
  }/*}}}*/

  vector<vector<int>> rem(c); // cycle pairs found
  { // Find cycles{{{
    vector<bool> seen(n, false);
    vector<int> st;
    set<pair<int,int>> remPairs;
    auto find_cycles = y_combinator([&](auto find_cycles, int i, int p) -> void {
      seen[i] = true;
      st.push_back(i);
      for (int j: adj[i]) if (j != p) {
        if (seen[j]) { // found cycle
          if (!remPairs.count({i, j})) {
            vector<int> cyc;
            for (int k = sz(st)-1; k >= 0; k--) {
              cyc.push_back(st[k]);
              if (st[k] == j) break;
            }
            remPairs.insert({i, j});
            remPairs.insert({j, i});

            map<int, int> indeg;
            for (auto x: cyc) indeg[x] = 0;
            F0R(k, sz(cyc)) {
              int u = cyc[k];
              int v = cyc[(k+1)%sz(cyc)];
              if (edges.count({u, v})) {
                indeg[v]++;
              }
              else indeg[u]++;
            }
            vector<int> c0, c2;
            for (auto [v, cnt]: indeg) {
              if (cnt == 0) c0.push_back(v);
              else if (cnt == 2) c2.push_back(v);
            }
            if (sz(c0) == 1 && sz(c2) == 1) {
              // cout << c0[0] << ' ' << c2[0] << endl;
              rem[c2[0]].push_back(c0[0]);
            }
          }
        }
        else {
          find_cycles(j, i);
        }
      }
      st.pop_back();
    });
    find_cycles(0, 0);
  }/*}}}*/

  ll ans = 0;
  vector<int> dp(c);
  F0R(i, c) {
    dp[i] = comp_size[i];
    for (int j: rev[i]) dp[i] += dp[j];
    for (int j: rem[i]) dp[i] -= dp[j];
    ans += 1LL * comp_size[i] * dp[i];
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
