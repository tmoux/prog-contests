#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll

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

const int maxn = 2e5+5;
int N, M;
vector<pair<int, int>> adj[maxn];

vector<int> dijkstra(int source) {
  const int INF = 2e9;
  vector<int> dist(M+2, INF);
  dist[source] = 0;
  using P = pair<int, int>;
  priority_queue<P, vector<P>, greater<P>> pq;
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

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  vector<pair<int, int>> pos(M+2);
  cin >> pos[M].first >> pos[M].second;
  cin >> pos[M+1].first >> pos[M+1].second;
  vector<array<int, 3>> Sx, Sy;
  F0R(i, M) {
    cin >> pos[i].first >> pos[i].second;
    Sx.push_back({pos[i].first, pos[i].second, i});
    Sy.push_back({pos[i].first, pos[i].second, i});
  }
  sort(all(Sx));
  sort(all(Sy), [&](auto a, auto b) {
    if (a[1] != b[1]) return a[1] < b[1];
    return a[0] < b[0];
  });

  auto dist = [&](pair<int, int> a, pair<int, int> b) {
    return min(abs(a.first - b.first), abs(a.second - b.second));
  };

  auto manhat = [&](pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
  };

  auto add_edge = [&](int a, int b, int w) {
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  };

  F0R(i, M) {
    if (i > 0) {
      int a = Sx[i][2];
      int b = Sx[i-1][2];
      add_edge(a, b, dist(pos[a], pos[b]));

      a = Sy[i][2];
      b = Sy[i-1][2];
      add_edge(a, b, dist(pos[a], pos[b]));
    }
  }

  F0R(i, M) {
    add_edge(i, M, dist(pos[i], pos[M]));
    add_edge(i, M+1, manhat(pos[i], pos[M+1]));
  }
  add_edge(M, M+1, manhat(pos[M], pos[M+1]));
  auto d = dijkstra(M);
  cout << d[M+1] << '\n';
}
