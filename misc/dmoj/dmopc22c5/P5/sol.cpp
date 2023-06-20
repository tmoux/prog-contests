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
int N, M;
char G[maxn][maxn];

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
bool valid(int i, int j) {
  return 0 <= i && i < N && 0 <= j && j < M;
}


vector<vector<pair<int, int>>> bad_pieces = {
{{0, 0}, {0, 1}, {0, 2}, {1, 1}, {-1, -1}},
{{0, 0}, {1, 0}, {2, 0}, {1, 1}, {1, -1}},
{{1, 0}, {1, 1}, {1, 2}, {0, 1}, {2, 1}},
{{0, 1}, {1, 1}, {2, 1}, {1, 0}, {1, 2}}, // T shape
};

bool B[maxn][maxn];
bool has_bad_shape(vector<pair<int, int>> piece, int i, int j) {
  F0R(idx, 4) {
    auto [di, dj] = piece[idx];
    if (!(valid(i + di, j + dj) && G[i+di][j+dj] == '#')) return false;
  }
  for (auto [di, dj]: piece) {
    if (valid(i+di, j+dj)) B[i+di][j+dj] = 1;
  }
  bool poss = 1;
  F0R(idx, 4) {
    auto [di, dj] = piece[idx];
    F0R(k, 4) {
      int ni = i + di + dx[k];
      int nj = j + dj + dy[k];
      if (valid(ni, nj) && !B[ni][nj] && G[ni][nj] == '#') {
        poss = 0;
        goto done;
      }
    }
  }
  done:
  for (auto [di, dj]: piece) {
    if (valid(i+di, j+dj)) B[i+di][j+dj] = 0;
  }
  return poss;
}


bool vis[maxn][maxn];
pair<bool, int> num_comps() {
  memset(vis, 0, sizeof vis);
  int comps = 0;
  bool has_isolated = false;
  F0R(i, N) {
    F0R(j, M) {
      if (G[i][j] == '#' && !vis[i][j]) {
        comps++;
        vis[i][j] = 1;
        queue<pair<int, int>> q;
        q.push({i, j});
        int sz = 0;
        while (!q.empty()) {
          auto [a, b] = q.front(); q.pop();
          sz++;
          F0R(k, 4) {
            int ni = a + dx[k];
            int nj = b + dy[k];
            if (valid(ni, nj) && G[ni][nj] == '#' && !vis[ni][nj]) {
              vis[ni][nj] = 1;
              q.push({ni, nj});
            }
          }
        }
        if (sz == 1) has_isolated = true;
      }
    }
  }
  for (auto piece: bad_pieces) {
    F0R(i, N) {
      F0R(j, M) {
        if (has_bad_shape(piece, i, j)) {
          has_isolated = 1;
          goto done;
        }
      }
    }
  }
  done:
  return {has_isolated, comps};
}

vector<vector<pair<int, int>>> pieces = {
{{0, 0}, {1, 0}},
{{0, 0}, {0, 1}},
{{0, 0}, {1, 0}, {2, 0}},
{{0, 0}, {0, 1}, {0, 2}},
{{0, 1}, {1, 0}, {1, 1}},
{{0, 0}, {1, 0}, {1, 1}},
{{0, 0}, {0, 1}, {1, 1}},
{{0, 0}, {0, 1}, {1, 0}},
};

bool can_place(vector<pair<int, int>> piece, int i, int j, int &comps) {
  for (auto [di, dj]: piece) {
    if (!(valid(i + di, j + dj) && G[i+di][j+dj] == '#')) return false;
  }
  // try place the piece
  vector<bool> next(26);
  for (auto [di, dj]: piece) {
    F0R(k, 4) {
      int ni = i + di + dx[k];
      int nj = j + dj + dy[k];
      if (valid(ni, nj) && 'A' <= G[ni][nj] && G[ni][nj] <= 'Z') {
        next[G[ni][nj]-'A'] = 1;
      }
    }
  }

  int c = -1;
  F0R(idx, 26) if (!next[idx]) {
    c = idx;
    break;
  }
  assert(c != -1);

  for (auto [di, dj]: piece) {
    G[i+di][j+dj] = 'A' + c;
  }
  // cout << "TRYING " << endl;
  // F0R(i, N) {
  //   F0R(j, M) {
  //     cout << G[i][j];
  //   }
  //   cout << endl;
  // }
  auto [has_isolated, new_comps] = num_comps();

  // cout << has_isolated << ' ' << new_comps << endl;
  if (new_comps <= comps && !has_isolated) {
    comps = new_comps;
    return true;
  }
  else {
    for (auto [di, dj]: piece) {
      G[i+di][j+dj] = '#';
    }
    return false;
  }
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, M) {
      G[i][j] = s[j];
    }
  }

  auto [has_isolated, comps] = num_comps();
  if (has_isolated) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  while (comps > 0) {
    // DEBUG(comps);
    // F0R(i, N) {
    //   F0R(j, M) {
    //     cout << G[i][j];
    //   }
    //   cout << endl;
    // }
    bool placed = 0;
    for (auto piece: pieces) {
      F0R(i, N) {
        F0R(j, M) {
          if (can_place(piece, i, j, comps)) {
            placed = 1;
            goto done;
          }
        }
      }
    }
    done: assert(placed);
  }

  F0R(i, N) {
    F0R(j, M) {
      cout << G[i][j];
    }
    cout << '\n';
  }
}
