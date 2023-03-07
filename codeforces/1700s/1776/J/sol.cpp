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

const int maxn = 105;
int N, M, K, C[maxn];
int g[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  F0R(i, N) cin >> C[i];
  F0R(i, M) {
    int a, b; cin >> a >> b; a--, b--;
    g[a][b] = g[b][a] = 1;
  }

  const int INF = 2e9;
  int ans = 0;
  F0R(i, N) {
    vector<int> dist(2*N, INF);
    dist[2*i] = 0;
    queue<int> q; q.push(2*i);
    while (!q.empty()) {
      auto f = q.front(); q.pop();
      int u = f / 2, p = f & 1;
      F0R(v, N) {
        if (g[u][v]) {
          int idx = v * 2 + (p ^ (C[u] != C[v]));
          if (dist[idx] > dist[f] + 1) {
            dist[idx] = dist[f] + 1;
            q.push(idx);
          }
        }
      }
    }

    F0R(j, N) {
      int mn = min(dist[j*2], dist[j*2+1]), mx = max(dist[j*2], dist[j*2+1]);
      if (mx < mn + K) ckmax(ans, (mn + mx + K) / 2);
      else ckmax(ans, mn + K);
    }
  }
  cout << ans << '\n';
}
