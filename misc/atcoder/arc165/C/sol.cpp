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

const int maxn = 2e5+5;
int N, M;
vector<pair<int, int>> adj[maxn];


int color[maxn];
bool is_bipartite;
void dfs(int i, int c, int X) {
  color[i] = c;
  for (auto [j, w]: adj[i]) {
    if (w < X) {
      if (color[j] == -1) {
        dfs(j, c^1, X);
      }
      else if (color[j] == color[i]) {
        is_bipartite = false;
      }
    }
  }
}

// 0: always possible, 1e9+9: impossible, since all are less than that.
// Can graph be colored s.t. every pair of red/blue is distance at least X
// away from each other?
// Any edge < X: MUST be different colors
// Check whether graph with all edges < X
// is bipartite and min distance between nodes in
// same component is at least X.
bool check(int X) {
  FOR(i, 1, N+1) color[i] = -1;
  is_bipartite = true;
  FOR(i, 1, N+1) {
    if (color[i] == -1) dfs(i, 0, X);
  }

  if (is_bipartite) {
    int min_dist = 2e9+15;
    FOR(i, 1, N+1) {
      // cout << i << ": " << color[i] << endl;
      vector<int> d;
      for (auto [j, w]: adj[i]) {
        if (w < X) d.push_back(w);
      }
      // sort(all(d));
      if (sz(d) >= 2) ckmin(min_dist, d[0] + d[1]);
    }
    return min_dist >= X;
  }
  else return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  REP(M) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  FOR(i, 1, N+1) {
    sort(all(adj[i]), [&](auto a, auto b) {
      return a.second < b.second;
    });
  }

  int lo = 0, hi = 2e9+9;
  while (lo + 1 < hi) {
    int mid = std::midpoint(lo, hi);
    (check(mid) ? lo : hi) = mid;
  }
  cout << lo << '\n';
}
