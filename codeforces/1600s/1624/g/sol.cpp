#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

struct Edge {
  int to, wt;
  bool blocked;
};

int solve() {
  int n, m; cin >> n >> m;
  vector<vector<Edge>> adj(n);
  REP(m) {
    int a, b, w; cin >> a >> b >> w;
    a--; b--;
    adj[a].push_back({b, w, false});
    adj[b].push_back({a, w, false});
  }

  vector<bool> vis(n, false);
  auto dfs = y_combinator([&](auto dfs, int i, int& cnt, int k) -> void {
    vis[i] = true;
    cnt++;
    for (const auto& e: adj[i]) {
      if (vis[e.to] || e.blocked || (e.wt & (1<<k))) continue;
      dfs(e.to, cnt, k);
    }
  });

  int ans = 0;
  for (int k = 30; k >= 0; k--) {
    int cnt = 0;
    vis.assign(n, false);
    dfs(0, cnt, k);
    if (cnt == n) {
      F0R(i, n) {
        for (auto& e: adj[i]) {
          if (e.wt & (1<<k)) {
            e.blocked = true;
          }
        }
      }
    }
    else {
      //cout << cnt << endl;
      //cout << "adding " <<  (1<<i) << endl;
      ans |= 1<<k;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
