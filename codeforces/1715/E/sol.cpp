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

typedef long double ld;

struct FN {
  ll xi, ci;  // in this case, function is a parabola
  // f(x) = (xi - x)^2 + ci
  FN(ll _xi, ll _ci) : xi(_xi), ci(_ci) {}
  ll eval(ll x) const {
    return (xi - x) * (xi - x) + ci;
  }

  ld intersect(const FN &r) const {  // returns x coordinate of intersection
    // assert(m != r.m);
    ld num = (xi * xi) - (r.xi * r.xi) + (ci - r.ci);
    ld den = 2 * (xi - r.xi);
    return num / den;
  }

  friend bool comp(const FN &l1, const FN &l2, const FN &l) {
    // order in deque: l1, l2, l
    // true --> l2 is unnecessary
    ld x1 = l1.intersect(l);
    ld x2 = l1.intersect(l2);
    return x1 <= x2;
  }
};

struct Hull : public deque<FN>  // convex hull for minimum
{
  void addFN(const FN &l) {
    while (size() >= 2 && comp((*this)[size() - 2], (*this)[size() - 1], l)) {
      this->pop_back();
    }
    this->push_back(l);
  }

  ll query(ll x) {
    if (size() == 0)
      return (1LL << 62);  // handle empty hull
    while (size() >= 2 && (*this)[1].eval(x) <= (*this)[0].eval(x)) {
      pop_front();
    }
    return (*this)[0].eval(x);
  }
};

const ll INF = 1e18;
int N, M, K;

vector<ll> dijkstra(int source, const vector<vector<pair<int, ll>>> &adj) {
  vector<ll> dist(N+1, INF);
  dist[source] = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;
  pq.push({0LL, source});
  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();
    if (d > dist[u])
      continue;
    for (auto [v, weight] : adj[u]) {
      if (dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M >> K;
  vector<vector<pair<int, ll>>> adj(N + 1);

  REP(M) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  vector<ll> ans(N + 1, INF);
  ans[0] = ans[1] = 0;
  for (int i = 1; i <= N; i++) {
    adj[0].push_back({i, i == 1 ? 0 : INF});
  }
  for (int k = 0; k <= K; k++) {
    for (auto &[i, d] : adj[0]) {
      d = ans[i];
    }
    ans = dijkstra(0, adj);

    /*
    cout << ans.size() << endl;
    cout << k << ": " << ans << '\n';
    */

    if (k+1 <= K) {
      Hull hull;
      for (int i = 1; i <= N; i++) {
        hull.addFN(FN(i, ans[i]));
      }
      for (int i = 1; i <= N; i++) {
        ans[i] = hull.query(i);
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
