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
bool ckmin(T &a, const T &b)
{
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b)
{
  return a < b ? a = b, 1 : 0;
}

namespace std
{
  template <class Fun>
  class y_combinator_result
  {
    Fun fun_;

  public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args &&...args)
    {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };

  template <class Fun>
  decltype(auto) y_combinator(Fun &&fun)
  {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
  os << '[';
  string sep;
  for (const T &x : v)
    os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 1e5 + 5;
const int INF = 2e9;
int N, M;

const int D = 12;
int cv(int i, int p)
{
  return i * D + (p % D);
}
vector<pair<int, int>> adj[maxn * D];

vector<int> dijkstra(int source)
{
  vector<int> dist(maxn * D, INF);
  dist[source] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0LL, source});
  while (!pq.empty())
  {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue;
    for (auto [v, weight] : adj[u])
    {
      if (dist[v] > dist[u] + weight)
      {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
  return dist;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M;
  REP(M)
  {
    int a, b, y;
    cin >> a >> b >> y;
    F0R(p, D)
    {
      adj[cv(a, p)].push_back({cv(b, p + y), y});
      adj[cv(b, p)].push_back({cv(a, p + y), y});
    }
  }

  auto d1 = dijkstra(cv(1, 0));
  auto d2 = dijkstra(cv(N, 0));

  for (int i = 1; i <= N; i++) {
    int ans = INF;
    F0R(p, D) {
      ckmin(ans, max(d1[cv(i, p)], d2[cv(i, p)]));
    }
    cout << (ans < INF ? ans : -1) << '\n';
  }
}