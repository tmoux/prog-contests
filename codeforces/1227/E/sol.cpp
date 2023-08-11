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

const int maxn = 1e6+6;
int N, M;
string GG[maxn], G[maxn], B[maxn], T[maxn];

bool flip = false;

bool valid(int i, int j) {
  return 0 <= i && i < N && 0 <= j && j < M;
}

vector<vector<int>> D;

// l       v     r
// T T T T F F F F
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}

vector<vector<bool>> vis;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    cin >> GG[i];
  }
  if (N > M) {
    flip = true;
    F0R(j, M) G[j].resize(N);
    F0R(i, N) {
      F0R(j, M) {
        G[j][i] = GG[i][j];
      }
    }
    swap(N, M);
  }
  else {
    F0R(i, N) G[i] = GG[i];
  }
  vis = vector<vector<bool>>(N, vector<bool>(M));
  F0R(i, N) {
    B[i] = G[i];
    T[i].resize(sz(G[i]));
  }
  const int INF = 2e9;
  D = vector(N, vector<int>(M, INF));
  queue<pair<int, int>> q;
  F0R(i, N) {
    F0R(j, M) {
      if (G[i][j] != 'X') continue;
      bool b = false;
      for (int dx : {-1, 0, 1}) {
        for (int dy : {-1, 0, 1}) {
          int ni = i + dx;
          int nj = j + dy;
          if (ni == i && nj == j) continue;
          if (!valid(ni, nj) || G[ni][nj] == '.') {
            b = true;
          }
        }
      }
      if (b) {
        q.push({i, j});
        D[i][j] = 0;
      }
    }
  }

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int dx : {-1, 0, 1}) {
      for (int dy : {-1, 0, 1}) {
        int ni = i + dx;
        int nj = j + dy;
        if (ni == i && nj == j) continue;
        if (valid(ni, nj) && G[ni][nj] == 'X' && D[ni][nj] > D[i][j] + 1) {
          D[ni][nj] = D[i][j] + 1;
          q.push({ni, nj});
        }
      }
    }
  }

  auto check = [&](int d) -> bool {
    queue<array<int, 3>> q;
    F0R(i, N) F0R(j, M) vis[i][j] = 0;
    F0R(i, N) {
      F0R(j, M) {
        if (G[i][j] == 'X' && D[i][j] >= d) {
          T[i][j] = 'X';
          vis[i][j] = 1;
          q.push({i, j, d});
        }
        else T[i][j] = '.';
      }
    }

    while (!q.empty()) {
      auto [i, j, x] = q.front(); q.pop();
      if (x > 0) {
        for (int dx : {-1, 0, 1}) {
          for (int dy : {-1, 0, 1}) {
            int ni = i + dx;
            int nj = j + dy;
            if (ni == i && nj == j) continue;
            if (valid(ni, nj) && !vis[ni][nj]) {
              vis[ni][nj] = 1;
              q.push({ni, nj, x-1});
            }
          }
        }
      }
    }


    bool ok = true;
    F0R(i, N) {
      F0R(j, M) {
        if (!(vis[i][j] == (G[i][j] == 'X'))) {
          ok = false;
          break;
        }
      }
    }
    return ok;
  };

  int ans = find_first_false(0, min(N, M), check) - 1;
  check(ans);

  cout << ans << '\n';
  if (!flip) {
    F0R(i, N) {
      cout << T[i] << '\n';
    }
  }
  else {
    F0R(j, M) {
      F0R(i, N) {
        cout << T[i][j];
      }
      cout << '\n';
    }
  }
}
