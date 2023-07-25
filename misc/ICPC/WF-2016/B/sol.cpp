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

const int maxn = 5005;
int N, B, S, M;

const ll INF = 1e18;
vector<pair<int, ll>> adj[maxn], radj[maxn];
vector<ll> dijkstra(int source) {
  vector<ll> dist(N+1, INF);
  dist[source] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, source});
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, weight] : adj[u]) {
      if (dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

ll dp[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> B >> S >> M;
  REP(M) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].push_back({b, w});
    radj[b].push_back({a, w});
  }

  auto d1 = dijkstra(B+1);
  swap(adj, radj);
  auto d2 = dijkstra(B+1);
  vector<ll> d(B+1);
  FOR(i, 1, B+1) d[i] = d1[i] + d2[i];
  sort(all(d));
  vector<ll> P(B+1);
  FOR(i, 1, B+1) {
    P[i] = d[i] + (i == 0 ? 0 : P[i-1]);
  }
  for (int i = 0; i <= B; i++) {
    for (int j = 0; j <= B; j++) {
      dp[i][j] = INF;
    }
  }
  dp[0][0] = 0;
  for (int i = 1; i <= B; i++) {
    for (int k = 0; k < i; k++) {
      for (int j = 0; j < i / (i - k); j++) {
        ckmin(dp[i][j+1], (i - k - 1) * (P[i] - P[k]) + dp[k][j]);
      }
    }
  }
  cout << dp[B][S] << '\n';
}
