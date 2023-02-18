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
  deque<pair<int, int>> pq;
  vector<vector<int>> dist(R, vector<int>(C, INF));
  vector<vector<bool>> procc(R, vector<bool>(C, 0));

  dist[sr][sc] = 0;
  pq.emplace_front(sr, sc);

  while (!pq.empty()) {
    auto [r, c] = pq.front(); pq.pop_front();
    procc[r][c] = true;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    F0R(k, 4) {
      int nr = r + dx[k];
      int nc = c + dy[k];
      if (0 <= nr && nr < R && 0 <= nc && nc < C) {
        int cost = g[nr][nc] == '#' ? 1 : 0;
        if (cost == 0 && dist[nr][nc] > dist[r][c] + cost) {
          dist[nr][nc] = dist[r][c] + cost;
          pq.emplace_front(nr, nc);
        }
      }
    }

    int xmin = -N, xmax = N;
    int ymin = -N, ymax = N;
    F0R(k, 4) {
      int nr = r + dx[k];
      int nc = c + dy[k];
      if (0 <= nr && nr < R && 0 <= nc && nc < C && procc[nr][nc]) {
        if (k == 0) ckmin(ymax, -N+1);
        if (k == 2) ckmax(ymin, N-1);
        if (k == 1) ckmin(xmax, -N+1);
        if (k == 3) ckmax(xmin, N-1);
      }
    }
    for (int dx = xmin; dx <= xmax; dx++) {
      for (int dy = ymin; dy <= ymax; dy++) {
        if (abs(dx) == N && abs(dy) == N) continue;
        int nr = r + dx;
        int nc = c + dy;
        if (0 <= nr && nr < R && 0 <= nc && nc < C && dist[nr][nc] > dist[r][c] + 1) {
          dist[nr][nc] = dist[r][c] + 1;
          pq.emplace_back(nr, nc);
        }
      }
    }
  }

  cout << dist[gr][gc] << '\n';
}
