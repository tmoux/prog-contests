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

const int maxn = 1005;
vector<int> adj[maxn];

bool vis[maxn];

int dist[maxn][maxn];

void dfs(int i, int o, int d, int& cnt) {
  if (vis[i]) return;
  dist[o][i] = d;
  vis[i] = 1;
  cnt++;
  for (int j: adj[i]) {
    dfs(j, o, d+1, cnt);
  }
}

void dfs2(int i, int p, vector<int>& path) {
  path.push_back(i);
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs2(j, i, path);
  }
}

int N;
int A[maxn];
void q1(int x) {
  cout << "+ " << x << endl;
  int r; cin >> r;
  assert(r == 1);

  FOR(i, 1, N+1) {
    if (1 <= x-i && x-i <= N) {
      if (i < x-i) {
        adj[i].push_back(x-i);
        adj[x-i].push_back(i);
      }
    }
  }
}

int q2(int i, int j) {
  cout << "? " << i << ' ' << j << endl;
  int r; cin >> r;
  // int r = dist[A[i]][A[j]];
  assert(r >= -1);
  assert(r >= 0);
  return r;
}

void solve() {
  cin >> N;
  // FOR(i, 1, N+1) {
  //   cin >> A[i];
  // }
  if (N == 2) {
    cout << "! 1 2 2 1" << endl;
    int r; cin >> r;
    return;
  }
  F0R(i, N+1) {
    vis[i] = 0;
    adj[i].clear();
    F0R(j, N+1) dist[i][j] = 0;
  }

  // make path
  if (N % 2 == 0) {
    q1(N + 1);
    q1(N / 2 + 1);
    q1(N + N / 2 + 2);
  }
  else {
    q1(N+1);
    if ((N-1) / 2 % 2 == 1) {
      q1(N/2 + 2);
      q1(N + N/2 + 2);
    }
    else {
      q1(N/2 + 2);
      q1(N + N/2 + 2);
    }
  }

  pair<int, int> mx = {0, 1};
  for (int i = 2; i <= N; i++) {
    ckmax(mx, {q2(1, i), i});
  }
  int c = mx.second;
  vector<pair<int, int>> v;
  v.push_back({0, c});
  v.push_back({mx.first, 1});
  for (int i = 2; i <= N; i++) {
    if (i == c) continue;
    int d = q2(c, i);
    v.push_back({d, i});
  }
  sort(all(v));

  vector<int> path;
  int s = -1;
  FOR(i, 1, N+1) {
    if (sz(adj[i]) == 1) {
      s = i;
      break;
    }
  }

  dfs2(s, s, path);
  // DEBUG(path);

  vector<int> ans1(N), ans2(N);
  F0R(i, N) {
    // ans1[path[i]-1] = v[i].second;
    ans1[v[i].second-1] = path[i];
  }
  reverse(all(path));
  F0R(i, N) {
    // ans2[path[i]-1] = v[i].second;
    ans2[v[i].second-1] = path[i];
  }

  // answer
  cout << "! ";
  for (auto x: ans1) cout << x << ' ';
  for (auto x: ans2) cout << x << ' ';
  cout << endl;
  int r; cin >> r;
  assert(r == 1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
