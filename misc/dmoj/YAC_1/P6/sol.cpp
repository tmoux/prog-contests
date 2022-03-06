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
const ll INF = 1e18;
int N, M;
struct Edge
{
  int to, weight;
};
vector<Edge> adj[maxn];

void add_edge(int a, int b, int w) {
  adj[a].push_back({b, w});
  adj[b].push_back({a, w});
}

vector<ll> dijkstra(int source) {
  vector<ll> dist(N+1,INF);
  dist[source] = 0;
  priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
  pq.push({0LL,source});
  while (!pq.empty()) {
    int u = pq.top().second; 
    int d = pq.top().first;
    pq.pop();
    if (d > dist[u]) continue; 
    for (Edge& e: adj[u]) {
      int v = e.to;
      ll weight = e.weight;
      if (dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v],v});
      }
    }
  }
  return dist;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // subtask 1: only type 2 alchemists
  cin >> N >> M;
  REP(M) {
    int t, k, s; cin >> t >> k >> s;
    assert(t == 2 && s == 0);
    REP(k) {
      int p, q, r; cin >> p >> q >> r;
      add_edge(p, q, r);
    }
  }

  auto dist = dijkstra(1);
  cout << dist[N] << '\n';
}
