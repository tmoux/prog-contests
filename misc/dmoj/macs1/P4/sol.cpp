#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 20005;
const ll INF = 1e18;
int N, M, K;
int p[5];

struct Edge
{
  int to, weight;
};
vector<Edge> adj[32*maxn];

vector<ll> dijkstra(int source) {
  vector<ll> dist(32*maxn,INF);
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

int cv(int mask, int i) {
  return mask * N + i;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  F0R(i, K) {
    cin >> p[i];
  }
  F0R(i, M) {
    int u, v, w; cin >> u >> v >> w;
    u--, v--;
    REP(2) {
      F0R(mask, 1<<K) {
        int a = cv(mask, u);
        int b = cv(mask, v);
        adj[a].push_back({b, w});
        F0R(mask2, 1<<K) {
          if ((mask2 & mask) == mask2) {
            bool poss = true;
            int nw = w;
            F0R(j, K) {
              if ((mask & (1<<j)) && !(mask2 & (1<<j))) {
                if (w & (1<<p[j])) {
                  nw ^= (1<<p[j]);
                }
                else {
                  poss = false;
                  break;
                }
              }
            }
            if (poss) {
              int nb = cv(mask2, v);
              adj[a].push_back({nb, nw});
            }
          }
        }
        // int a = cv(mask, u);
        // int b = cv(mask, v);
        // adj[a].push_back({b, w});
        // F0R(j, K) if ((mask & (1<<j)) && (w & (1<<j))) {
        //   int nmask = mask ^ (1<<j);
        //   int nw = w ^ (1<<j);
        //   int nb = cv(nmask, v);
        //   adj[a].push_back({nb, nw});
        // }
      }
      swap(u, v);
    }
  }

  auto dist = dijkstra(cv((1<<K)-1, 0));

  ll ans = INF;
  F0R(mask, 1<<K) {
    ckmin(ans, dist[cv(mask, N-1)]);
  }
  cout << ans << '\n';
}
