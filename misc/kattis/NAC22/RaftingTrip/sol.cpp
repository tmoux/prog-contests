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

const int maxn = 505;
int N, M;
char grid[maxn][maxn];

int g[maxn*maxn];
vector<int> gr[maxn*maxn];

map<char, pair<int,int>> mp = {
  {'v', {1, 0}},
  {'^', {-1, 0}},
  {'>', {0, 1}},
  {'<', {0, -1}},
};

bool isriver(char c) {
  return c == 'v' || c == '^' || c == '>' || c == '<';
}
bool isvalid(int i, int j) {
  return 0 <= i && i < N && 0 <= j && j < M;
}
int cv(int i, int j) {
  return i*M + j;
}

bool vis[maxn*maxn], onstack[maxn*maxn];
vector<int> st;
vector<vector<int>> cycles;
void dfs(int i) {
  if (vis[i]) return;
  vis[i] = true;
  onstack[i] = true;
  st.push_back(i);

  if (g[i] != -1) {
    int j = g[i];
    if (onstack[j]) {
      vector<int> cyc;
      for (int k = sz(st)-1; k >= 0; k--) {
        cyc.push_back(st[k]);
        if (st[k] == j) break;
      }
      cycles.push_back(cyc);
    }
    dfs(j);
  }

  onstack[i] = false;
  st.pop_back();
}

vector<int> sights[maxn*maxn];
int sight_vis[maxn*maxn];

int ans = 0;

void dfs2(int i, int& cur_ans) {
  vector<int> add;
  for (int j: sights[i]) {
    if (!sight_vis[j]) {
      sight_vis[j] = true;
      cur_ans++;
      add.push_back(j);
    }
  }

  ckmax(ans, cur_ans);

  for (auto j: gr[i]) {
    dfs2(j, cur_ans);
  }

  for (auto j: add) {
    sight_vis[j] = false;
    cur_ans--;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    F0R(j, M) {
      cin >> grid[i][j];
    }
  }

  F0R(i, N) {
    F0R(j, M) {
      if (isriver(grid[i][j])) {
        int ni = i + mp[grid[i][j]].first;
        int nj = j + mp[grid[i][j]].second;
        if (isvalid(ni, nj) && isriver(grid[ni][nj])) {
          g[cv(i, j)] = cv(ni, nj);
          gr[cv(ni, nj)].push_back(cv(i, j));
        }
        else g[cv(i, j)] = -1;
      }
    }
  }

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  F0R(i, N) {
    F0R(j, M) {
      if (isriver(grid[i][j])) {
        F0R(k, 4) {
          int ni = i + dx[k];
          int nj = j + dy[k];
          if (isvalid(ni, nj) && grid[ni][nj] == '#') {
            sights[cv(i, j)].push_back(cv(ni, nj));
          }
        }
      }
    }
  }

  F0R(i, N) {
    F0R(j, M) {
      if (isriver(grid[i][j]) && !vis[cv(i, j)]) dfs(cv(i, j));
    }
  }

  vector<bool> cur_cycle(N*M, false);
  for (const auto& v: cycles) {
    int cur_ans = 0;
    for (auto x: v) {
      for (int j: sights[x]) {
        if (!sight_vis[j]) {
          sight_vis[j] = true;
          cur_ans++;
        }
      }
      cur_cycle[x] = true;
    }

    ckmax(ans, cur_ans);
    for (auto x: v) for (int i: gr[x]) {
      if (!cur_cycle[i]) {
        dfs2(i, cur_ans);
      }
    }

    for (auto x: v) {
      for (int j: sights[x]) sight_vis[j] = false;
      cur_cycle[x] = false;
    }
  }

  F0R(i, N) {
    F0R(j, M) {
      if (g[cv(i, j)] == -1) {
        int cur_ans = 0;
        dfs2(cv(i, j), cur_ans);
      }
    }
  }

  cout << ans << '\n';
}
