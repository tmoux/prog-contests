#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}

const int MAXN = 305;

// int on[MAXN][MAXN][MAXN];
int N, Q;

int dist[MAXN][MAXN];

char g[MAXN][MAXN];

bool valid(int i, int j) {
  return 0 <= i && i < N && 0 <= j && j < N;
}
map<char, int> dx = {
{'U', -1},
{'D', 1},
{'L', 0},
{'R', 0},
};

map<char, int> dy = {
{'U', 0},
{'D', 0},
{'L', -1},
{'R', 1},
};

int ANS[MAXN];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  vector<pair<pair<int, int>, char>> v;
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, N) {
      g[i][j] = s[j];
      if (g[i][j] != '.') {
        v.push_back({{i, j}, g[i][j]});
      }
    }
  }

  for (int t = 0; t < MAXN; t++) {
    memset(dist, -1, sizeof dist);
    // find answer for dist 0
    deque<array<int, 2>> q;
    int d = g[N-1][N-1] != '.';
    dist[N-1][N-1] = d;
    if (!d) q.push_front({N-1, N-1});
    else q.push_back({N-1, N-1});

    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop_front();
      int Dx[] = {0, 1, 0, -1};
      int Dy[] = {1, 0, -1, 0};
      F0R(k, 4) {
        int ni = i + Dx[k];
        int nj = j + Dy[k];
        if (valid(ni, nj)) {
          int c = g[ni][nj] != '.';
          if (dist[ni][nj] == -1) {
            dist[ni][nj] = dist[i][j] + c;
            // cout << "HUH " << t << ' ' << i << ' ' << j << ": " << dist[t][i][j] << ' ' << c << endl;
            // assert(dist[t][ni][nj] >= 0);
            if (!c) q.push_front({ni, nj});
            else q.push_back({ni, nj});
          }
        }
      }
    }
    ANS[t] = dist[0][0];

    for (auto& [loc, c]: v) {
      auto& [x, y] = loc;
      int nx = x + dx[c];
      int ny = y + dy[c];
      if (valid(nx, ny)) {
        g[nx][ny] = c;
        x = nx;
        y = ny;
      }
    }
  }

  // answer queries
  while (Q--) {
    int t; cin >> t; t--;
    // DEBUG(t);
    cout << ANS[min(N, t)] << '\n';
  }
}
