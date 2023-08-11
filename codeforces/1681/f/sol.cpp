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

const int maxn = 5e5+5;
int N;
struct Edge {
  int to, w;
};
vector<Edge> adj[maxn];

int subtree_size[maxn];

stack<int> vs[maxn];
vector<pair<int, int>> queries[maxn]; // color, index
void dfs(int i, int p, int c) {
  subtree_size[i] = 1;
  if (c != 0) {
    int j = vs[c].empty() ? 1 : vs[c].top();
    queries[j].push_back({c, i});
  }
  vs[c].push(i);
  for (auto [j, nc]: adj[i]) {
    if (j == p) continue;
    dfs(j, i, nc);
    subtree_size[i] += subtree_size[j];
  }
  vs[c].pop();
}

map<int, int> mp[maxn];
int down_cnt[maxn], up_cnt[maxn];

void merge(int i, int j, int c) {
  int c_val = mp[i][c] + subtree_size[j];
  if (sz(mp[i]) < sz(mp[j])) swap(mp[i], mp[j]);
  for (auto [x, y]: mp[j]) {
    if (x != c) mp[i][x] += y;
  }
  mp[i][c] = c_val;
}

void dfs2(int i, int p, int c) {
  for (auto [j, nc]: adj[i]) {
    if (j == p) continue;
    dfs2(j, i, nc);
    merge(i, j, nc);
  }
  down_cnt[i] = subtree_size[i] - mp[i][c];
  for (auto [color, idx]: queries[i]) {
    up_cnt[idx] = subtree_size[i] - mp[i][color];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  REP(N-1) {
    int u, v, x; cin >> u >> v >> x;
    adj[u].push_back({v, x});
    adj[v].push_back({u, x});
  }

  dfs(1, 0, 0); 
  dfs2(1, 0, 0);

  ll ans = 0;
  for (int i = 2; i <= N; i++) {
    ans += 1LL * down_cnt[i] * up_cnt[i];
  }
  cout << ans << '\n';
}
