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

const int maxn = 606;
const ll INF = 1e18;
int N, M, Q;
ll dist[maxn][maxn];

vector<pair<int, ll>> T[maxn];
ll mostExcess[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) F0R(j, N) if (i != j) dist[i][j] = INF;
  vector<array<int, 3>> edges;
  REP(M) {
    int u, v, w; cin >> u >> v >> w;
    u--, v--;
    dist[u][v] = dist[v][u] = w;
    edges.push_back({u, v, w});
  }
  F0R(k, N) {
    F0R(i, N) {
      F0R(j, N) {
        ckmin(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  cin >> Q;
  REP(Q) {
    int u, v, l; cin >> u >> v >> l;
    u--, v--;
    T[u].push_back({v, l});
    T[v].push_back({u, l});
  }

  F0R(i, N) F0R(j, N) mostExcess[i][j] = -INF;
  F0R(u, N) {
    F0R(b, N) {
      for (auto [v, l]: T[u]) {
        ckmax(mostExcess[u][b], l - dist[b][v]);
      }
    }
  }

  int ans = 0;
  for (auto [a, b, w]: edges) {
    bool poss = false;
    F0R(u, N) {
      ll d1 = dist[u][a] + w;
      poss |= d1 <= mostExcess[u][b];

      ll d2 = dist[u][b] + w;
      poss |= d2 <= mostExcess[u][a];
    }
    if (poss) ans++;
  }
  cout << ans << '\n';
}
