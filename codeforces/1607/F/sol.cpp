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

const int maxn = 2005;
int N, M;
string V[maxn];

map<char, pair<int, int>> mp = {
{'L', {0, -1}},
{'R', {0, 1}},
{'U', {-1, 0}},
{'D', {1, 0}},
};

bool valid(int a, int b) {
  return 0 <= a && a < N && 0 <= b && b < M;
};

pair<int, int> next(int i, int j) {
  int ni = i + mp[V[i][j]].first;
  int nj = j + mp[V[i][j]].second;
  if (valid(ni, nj)) return {ni, nj};
  else return {i, j};
};

vector<pair<int, int>> adj(int i, int j) {
  vector<pair<int, int>> v;
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};
  F0R(k, 4) {
    int ni = i + dx[k];
    int nj = j + dy[k];
    if (valid(ni, nj) && next(ni, nj) == make_pair(i, j)) v.push_back({ni, nj});
  }
  return v;
};

bool vis[maxn][maxn], st[maxn][maxn], seen[maxn][maxn];
int len[maxn][maxn];
queue<pair<int, int>> q;

void DFS(int i, int j) {
  vector<pair<int, int>> o;
  while (true) {
    o.push_back({i, j});
    st[i][j] = 1;
    auto [ni, nj] = next(i, j);
    if (vis[ni][nj]) break;
    else if (st[ni][nj]) {
      vector<pair<int, int>> cyc;
      for (int k = sz(o)-1; ; k--) {
        cyc.push_back(o[k]);
        if (o[k] == make_pair(ni, nj)) break;
      }
      for (auto [a, b]: cyc) {
        len[a][b] = sz(cyc);
        seen[a][b] = 1;
        q.push({a, b});
      }
      break;
    }
    else {
      i = ni, j = nj;
    }
  }

  for (auto [a, b]: o) {
    vis[a][b] = 1;
    st[a][b] = 0;
  }
};

void solve() {
  cin >> N >> M;
  F0R(i, N) {
    cin >> V[i];
  }
  F0R(i, N) {
    F0R(j, M) {
      vis[i][j] = st[i][j] = seen[i][j] = len[i][j] = 0;
    }
  }

  F0R(i, N) F0R(j, M) if (!vis[i][j]) DFS(i, j);
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (auto [ni, nj]: adj(i, j)) {
      if (!seen[ni][nj]) {
        seen[ni][nj] = 1;
        len[ni][nj] = len[i][j] + 1;
        q.push({ni, nj});
      }
    }
  }

  pair<int, pair<int, int>> best = {-1, {-1, -1}};
  F0R(i, N) {
    F0R(j, M) {
      ckmax(best, {len[i][j], {i, j}});
    }
  }

  cout << best.second.first+1 << ' ' << best.second.second+1 << ' ' << best.first << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
