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

int solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  vector<vector<pair<int, int>>> adj(N);
  F0R(i, N) {
    if (i > 0) adj[i].emplace_back(i-1, 1);
    if (i + 1 < N) adj[i].emplace_back(i+1, 1);
  }
  vector<pair<int, int>> v;
  F0R(i, N) v.push_back({A[i], i});
  sort(all(v));
  F0R(i, N-1) {
    auto [x, a] = v[i];
    auto [y, b] = v[i+1];
    adj[a].emplace_back(b, y - x);
    adj[b].emplace_back(a, y - x);
  }

  auto dijkstra = [&](int source) -> vector<int> {
    const int INF = 2e9;
    vector<int> dist(N, INF);
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
  };

  int ans = 0;
  F0R(i, N) {
    auto d = dijkstra(i);
    ckmax(ans, *max_element(all(d)));
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
