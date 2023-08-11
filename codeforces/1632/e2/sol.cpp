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

const int INF = 1e9;

void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  REP(n-1) {
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  auto bfs = [&](int b) -> vector<int> {/*{{{*/
    vector<int> dist(n);
    vector<bool> vis(n, false);
    queue<int> q;
    q.push(b);
    dist[0] = dist[b] = 0;
    while (!q.empty()) {
      int f = q.front(); q.pop();
      if (!vis[f]) {
        vis[f] = true;
        for (int j: adj[f]) if (!vis[j]) {
          dist[j] = dist[f] + 1;
          q.push(j);
        }
      }
    }
    return dist;
  };/*}}}*/

  auto dist0 = bfs(0);
  pair<int,int> mx = {-1, -1};
  vector<vector<int>> levels(n);
  F0R(i, n) {
    ckmax(mx, {dist0[i], i});
    levels[dist0[i]].push_back(i);
  }
  int L1 = mx.second;
  auto distToL1 = bfs(L1);
  vector<int> distByLevel(n, 0);
  set<pair<int,int>> nodes;
  F0R(i, n) {
    ckmax(distByLevel[dist0[i]], distToL1[i]);
  }
  for (int i = dist0[L1]-1; i >= 0; i--) {
    ckmax(distByLevel[i], distByLevel[i+1]);
  }

  vector<int> ans(n+1, INF);
  ans[n] = dist0[L1];
  for (int d = 0; d < dist0[L1]; d++) {
    int maxd = distByLevel[d+1];
    int R = (maxd+1)/2;
    int x = d - R;

    if (x >= 0) {
      ckmin(ans[x], d);
    }
  }
  for (int x = n-1; x >= 1; x--) {
    ckmin(ans[x], ans[x+1]);
  }
  for (int x = 1; x <= n; x++) {
    cout << ans[x] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
