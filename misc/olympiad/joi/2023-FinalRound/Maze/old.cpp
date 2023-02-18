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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int R, C, N; cin >> R >> C >> N;
  int sr, sc; cin >> sr >> sc; sr--, sc--;
  int gr, gc; cin >> gr >> gc; gr--, gc--;
  vector<string> g(R);
  F0R(i, R) cin >> g[i];

  const int INF = 2e9;
  vector<vector<int>> dist(R, vector<int>(C, INF));

  deque<pair<int, int>> q;
  dist[sr][sc] = 0;
  q.push_back({sr, sc});

  while (!q.empty()) {
    auto [r, c] = q.front(); q.pop_front();
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    F0R(k, 4) {
      int nr = r + dx[k];
      int nc = c + dy[k];
      if (0 <= nr && nr < R && 0 <= nc && nc < C) {
        int cost = g[nr][nc] == '#' ? 1 : 0;
        if (cost == 0 && dist[nr][nc] > dist[r][c] + cost) {
          dist[nr][nc] = dist[r][c] + cost;
          q.push_front({nr, nc});
        }
        else if (cost == 1 && dist[nr][nc] > dist[r][c] + cost) {
          dist[nr][nc] = dist[r][c] + cost;
          q.push_back({nr, nc});
        }
      }
    }
  }

  cout << dist[gr][gc] << '\n';
}
