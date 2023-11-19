#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

// Type 1: block everything
// Type 2: block all but shortest path
// Type 3: find pair of exits with shortest total path length
// Brute force the branching square, maintain closest 2 nearest exits

int solve() {
  int N, M; cin >> N >> M;
  pair<int, int> C = {-1, -1};
  vector<string> G(N);

  int free = 0;
  auto valid = [&](int i, int j) -> bool {
    return 0 <= i && i < N && 0 <= j && j < M;
  };
  auto isBoundary = [&](int i, int j) -> bool {
    return G[i][j] != '#' && (i == 0 || i == N-1 || j == 0 || j == M-1);
  };

  queue<pair<int, int>> q;
  vector<vector<int>> dist(N, vector<int>(M, 1e9));
  F0R(i, N) {
    cin >> G[i];
    F0R(j, M) {
      if (G[i][j] == '.') free++;
      if (G[i][j] == 'V') {
        C = {i, j};
      }
    }
  }
  q.push({C.first, C.second});
  dist[C.first][C.second] = 0;

  const int dx[] = {1, 0, -1, 0};
  const int dy[] = {0, 1, 0, -1};
  int mindist = 1e9;
  int num_exits = 0;
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    if (isBoundary(i, j)) {
      num_exits++;
      ckmin(mindist, dist[i][j]);
    }
    F0R(k, 4) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (valid(ni, nj) && G[ni][nj] != '#') {
        if (dist[ni][nj] > dist[i][j] + 1) {
          dist[ni][nj] = dist[i][j] + 1;
          q.push({ni, nj});
        }
      }
    }
  }

  if (num_exits == 0) {
    return free;
  }
  else if (num_exits == 1) {
    return free - mindist;
  }
  else {
    vector<vector<vector<array<int, 3>>>> exits(N, vector<vector<array<int, 3>>>(M));

    F0R(i, N) {
      F0R(j, M) {
        if (isBoundary(i, j)) {
          q.push({i, j});
          exits[i][j].push_back({i, j, 0});
        }
      }
    }
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      F0R(k, 4) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (valid(ni, nj) && G[ni][nj] != '#') {
          if (sz(exits[ni][nj]) < 2) {
            for (auto [a, b, c]: exits[i][j]) {
              bool has = false;
              for (auto [x, y, z]: exits[ni][nj]) {
                if (a == x && b == y) has = true;
              }
              if (!has && sz(exits[ni][nj]) < 2) {
                exits[ni][nj].push_back({a, b, c+1});
                q.push({ni, nj});
              }
            }
          }
        }
      }
    }
    int need = 1e9;
    F0R(i, N) {
      F0R(j, M) {
        if (dist[i][j] < 1e9) {
          assert(exits[i][j].size() == 2);
          ckmin(need, dist[i][j] + exits[i][j][0][2] + exits[i][j][1][2]);
        }
      }
    }
    return free - need;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
