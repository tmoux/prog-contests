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
  vector<vector<pair<int, int>>> adj(N);
  vector<pair<int, int>> edges;
  map<pair<int, int>, int> toEdge;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    edges.push_back({a, b});
    toEdge[{a, b}] = i;
    toEdge[{b, a}] = i;
    adj[a].emplace_back(b, i);
    adj[b].emplace_back(a, i);
  }
  vector<bool> vis(N);

  string ans(M, '0');
  set<int> reds;
  set<int> vs;
  vector<int> depth(N), par(N);
  auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
    vis[i] = true;
    par[i] = p;
    depth[i] = depth[p] + 1;
    for (auto [j, id]: adj[i]) {
      if (j == p) continue;
      if (!vis[j]) {
        dfs(j, i);
      }
      else {
        ans[id] = '1';
        reds.insert(id);
        vs.insert(i);
        vs.insert(j);
      }
    }
  });
  dfs(0, 0);

  if (sz(reds) == 3 && sz(vs) == 3) {
    // remove triangle
    pair<int, int> lowest = {-1, -1};
    pair<int, int> highest = {1e9, -1};
    for (int i: vs) {
      ckmax(lowest, {depth[i], i});
      ckmin(highest, {depth[i], i});
    }
    int i = lowest.second;
    int j = highest.second;
    int p = par[i];
    int e1 = toEdge[{i, j}];
    int e2 = toEdge[{i, p}];
    ans[e1] = '0';
    ans[e2] = '1';
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
