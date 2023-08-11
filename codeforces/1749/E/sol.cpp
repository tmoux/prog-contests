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

void solve() {
  int N, M; cin >> N >> M;
  vector<string> A(N);
  F0R(i, N) {
    cin >> A[i];
  }

  auto valid = [&](int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  };

  auto can_place = [&](int i, int j) {
    const int dx[] = {0, 1, 0, -1}; 
    const int dy[] = {1, 0, -1, 0};

    bool poss = valid(i, j);
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];

      if (valid(ni, nj) && A[ni][nj] == '#') poss = false;
    }
    return poss;
  };

  const int INF = 2e9;
  vector<vector<int>> dist(N, vector<int>(M, INF));
  vector<vector<pair<int,int>>> prev(N, vector<pair<int,int>>(M, {-1, -1}));
  deque<pair<int,int>> q;
  F0R(i, N) {
    if (A[i][0] == '#') {
      dist[i][0] = 0;
      q.push_front({i, 0});
    }
    else if (can_place(i, 0)) {
      dist[i][0] = 1;
      q.push_back({i, 0});
    }
  }

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop_front();

    const int dx[] = {1, 1, -1, -1};
    const int dy[] = {1, -1, 1, -1};

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k];
      int nj = j + dy[k];

      if (valid(ni, nj) && can_place(ni, nj)) {
        if (A[ni][nj] == '#') {
          if (dist[ni][nj] > dist[i][j]) {
            dist[ni][nj] = dist[i][j];
            prev[ni][nj] = {i, j};
            q.push_front({ni, nj});
          }
        }
        else {
          if (dist[ni][nj] > dist[i][j] + 1) {
            dist[ni][nj] = dist[i][j] + 1;
            prev[ni][nj] = {i, j};
            q.push_back({ni, nj});
          }
        }
      }
    }
  }

  pair<int, pair<int, int>> best = {INF, {-1, -1}};
  F0R(i, N) {
    if (dist[i][M-1] < best.first) {
      ckmin(best, {dist[i][M-1], {i, M-1}});
    }
  }

  if (best.first < INF) {
    int i = best.second.first; 
    int j = best.second.second; 
    while (i >= 0 && j >= 0) {
      A[i][j] = '#';
      auto [ni, nj] = prev[i][j];
      i = ni, j = nj;
    }
    cout << "YES\n";
    F0R(i, N) {
      cout << A[i] << '\n';
    }
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
