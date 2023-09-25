#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #define int ll

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

const int INF = 2e9+9, maxn = 20005, B = 150;
int N, C;
int deg[maxn], depth[maxn];
vector<pair<int, int>> adj[maxn];
vector<int> V;
int parEdge[maxn];
vector<int> block[B];
int specialD;

void prep(int i, int p) {
  deg[i] = sz(adj[i]);
  block[depth[i] % B].push_back(i);
  for (auto [j, w]: adj[i]) {
    if (j == p) continue;
    depth[j] = depth[i] + 1;
    parEdge[j] = w;
    prep(j, i);
  }
}

struct DP {
  vector<int> dp1a, dp1b;
  int dp2;
  DP() {
  }
  int mindp() {
    return min({dp2, *min_element(all(dp1a)), *min_element(all(dp1b))});
  }
};

DP memo[maxn];

int root = 1;
void dfs(int i, int p) {
  if (!memo[i].dp1a.empty()) return;
  DP dp;
  dp.dp1a.resize(sz(V), INF);
  dp.dp1b.resize(sz(V), INF);
  dp.dp2 = 0;
  if (sz(adj[i]) == 1) {
    memo[i] = dp;
    return;
  }

  int minw = 0;
  for (auto [j, w]: adj[i]) ckmax(minw, w);
  for (int W = minw; W < sz(V); W++) {
    dp.dp1a[W] = V[W] * deg[i] + (i == root ? 0 : -V[parEdge[i]]);
  }
  for (int W = parEdge[i]; W < sz(V); W++) {
    dp.dp1b[W] = C * deg[i] + (i == root ? 0 : V[W] - V[parEdge[i]]);
  }
  dp.dp2 += C * deg[i];
  for (auto [j, w]: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    auto& dpj = memo[j];
    int mindpj = dpj.mindp();
    for (int W = minw; W < sz(V); W++) {
      dp.dp1a[W] += min(dpj.dp2 - V[w],
                        min(dpj.dp1a[W], dpj.dp1b[W]) - V[W]);
    }
    for (int W = parEdge[i]; W < sz(V); W++) {
      dp.dp1b[W] += mindpj;
    }
    dp.dp2 += mindpj;

    if (depth[j] % B != specialD) {
      dpj.dp1a.clear();
      dpj.dp1b.clear();
    }
  }

  // cout << i << ": " << dp.mindp() << endl;
  // DEBUG(dp.dp1a);
  // DEBUG(dp.dp1b);
  // DEBUG(dp.dp2);
  memo[i] = dp;
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> C;
  vector<array<int, 3>> edges;
  REP(N-1) {
    int u, v, w; cin >> u >> v >> w;
    edges.push_back({u, v, w});
    V.push_back(w);
  }
  sort(all(V)); V.erase(unique(all(V)), V.end());
  for (auto& [u, v, w]: edges) {
    w = std::distance(V.begin(), lower_bound(all(V), w));
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  if (N <= 2) {
    cout << 0 << '\n';
    return 0;
  }

  while (sz(adj[root]) == 1) root++;
  assert(root <= N);
  prep(root, root);

  pair<int, int> mn = {2e9, -1};
  F0R(i, B) {
    ckmin(mn, {sz(block[i]), i});
  }
  specialD = mn.second;
  sort(all(block[specialD]), [&](int a, int b) {
    return depth[a] > depth[b];
  });
  DEBUG(specialD);
  for (int i: block[specialD]) {
    dfs(i, i);
  }

  dfs(root, root);
  cout << memo[root].mindp() << '\n';
}
