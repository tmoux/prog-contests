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

struct LineTracker {
  multiset<int> starts;
  int maxConst;

  vector<pair<int,int>> changes;
  LineTracker(const vector<int>& dist0, 
              const vector<int>& distb) {
    maxConst = 0;
    for (int i = 0; i < sz(dist0); i++) {
      if (distb[i] >= dist0[i]) {
        ckmax(maxConst, dist0[i]);
      }
      else {
        starts.insert(distb[i]);
        changes.push_back({dist0[i]-distb[i], distb[i]});
      }
    }
    sort(all(changes)); reverse(all(changes));
  }

  int query(int x) {
    while (!changes.empty() && changes.back().first <= x) {
      auto [t, a] = changes.back();
      changes.pop_back();
      starts.erase(starts.find(a));
      ckmax(maxConst, a+t);
    }
    if (starts.empty()) return maxConst;
    else return max(*starts.rbegin() + x, maxConst);
  }
};
void solve() {
  int n; cin >> n;
  vector<vector<int>> adj(n);
  REP(n-1) {
    int u, v; cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  auto bfs = [&](int b) -> vector<int> {
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
  };
  auto dist0 = bfs(0);

  const int INF = 1e9;
  vector<int> ans(n+1, INF);
  for (int b = 0; b < n; b++) {
    auto distb = bfs(b);
    LineTracker tracker(dist0, distb);
    for (int x = 1; x <= n; x++) {
      ckmin(ans[x], tracker.query(x));
    }
  }
  for (int x = 1; x <= n; x++) {
    cout << ans[x] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
