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

const int maxn = 105;
int N, M;
const int INF = 2e9;
int dist[maxn][maxn];

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    FOR(j, 1, N+1) {
      if (i != j) dist[i][j] = INF;
    }
  }
  REP(M) {
    int u, v, y; cin >> u >> v >> y;
    dist[u][v] = dist[v][u] = y;
  }

  vector<int> prev(N+1, -1);
  vector<ll> d(N+1, 1e18);
  d[1] = 0;
  vector<int> vis = {1};
  while (1) {
    const ll MX = 1e18;
    array<ll, 3> nxt = {MX, -1, -1};
    for (int i: vis) {
      FOR(j, 1, N+1) {
        if (prev[j] == -1 && dist[i][j] < INF) {
          ckmin(nxt, {d[i] + dist[i][j], j, i});
        }
      }
    }
    auto [dd, j, i] = nxt;
    if (j == -1) break;
    prev[j] = i;
    d[j] = dd;
    vis.push_back(j);
  }

  if (prev[N] == -1) {
    cout << "inf" << '\n';
  }
  else {
    if (d[N] == 0) {
      cout << 0 << ' ' << 0 << '\n';
      return 0;
    }
    vector<int> path;
    int cur = N;
    while (1) {
      path.push_back(cur);
      if (cur == 1) break;
      else cur = prev[cur];
    }
    reverse(all(path));

    vector<pair<vector<int>, ll>> ret;
    vector<ll> distances;
    FOR(i, 1, N+1) distances.push_back(d[i]);
    sort(all(distances)); distances.erase(unique(all(distances)), distances.end());

    ll prevDist = 0;
    for (auto di: distances) {
      if (di == 0) continue;
      vector<int> v(N+1, 0);
      FOR(i, 1, N+1) {
        if (d[i] < di) v[i] = 1;
      }
      assert(v[1] == 1 && v[N] == 0);
      ret.push_back({v, di-prevDist});
      prevDist = di;
      if (di == d[N]) break;
    }
    cout << d[N] << ' ' << sz(ret) << '\n';

    for (auto [v, di]: ret) {
      FOR(i, 1, N+1) {
        cout << v[i];
      }
      cout << ' ' << di << '\n';
    }
  }
}
