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
int n;
int X[maxn], Y[maxn];

vector<vector<int>> g, gr;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
  used[v] = true;
  for (int i = 0; i < sz(g[v]); i++)
    if (!used[g[v][i]])
      dfs1(g[v][i]);
  order.push_back(v);
}

void dfs2(int v) {
  used[v] = true;
  component.push_back(v);
  for (int i = 0; i < sz(gr[v]); i++) {
    if (!used[gr[v][i]])
      dfs2(gr[v][i]);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  g = vector<vector<int>>(n);
  gr = vector<vector<int>>(n);
  used = vector<bool>(n, false);

  for (int i = 0; i < n; i++) {
    cin >> X[i] >> Y[i];
    int f; cin >> f;
    REP(f) {
      int j; cin >> j; j--;
      g[i].push_back(j);
      gr[j].push_back(i);
    }
  }

  used.assign(n, false);
  for (int i=0; i<n; ++i)
    if (!used[i])
      dfs1(i);

  vector<int> comp(n, -1);
  vector<vector<int>> indices;
  order.clear();
  used.assign(n, false);
  int c = 0;
  for (int i=0; i<n; ++i) {
    int v = order[n-1-i];
    if (!used[v]) {
      dfs2(v);

      for (auto x: component) {
        comp[x] = c;
      }
      indices.push_back(component);
      component.clear();
      c++;
    }
  }

  set<pair<int,int>> edges; // edges in condensation graph
  vector<vector<int>> adj(c);

  F0R(i, n) {
    int a = comp[i];
    for (int j: g[i]) {
      int b = comp[j];
      if (a != b) {
        assert(a < b);
        edges.insert({a, b});
      }
    }
  }

  for (auto [u, v]: edges) {
    adj[u].push_back(v);
  }

  const int INF = 2e9;
  vector<vector<int>> dp(c, vector<int>(n+1, INF));
  for (int i = 0; i < c; i++) dp[i][0] = 0;
  for (int i = 0; i < c; i++) {
    int m = sz(indices[i]);
    vector<int> cost(m+1, INF);
    cost[0] = 0;
    multiset<int> ms;
    for (auto x: indices[i]) {
      ms.insert(X[x]);
    }
    for (auto x: indices[i]) {
      auto it = ms.find(X[x]);
      assert(it != ms.end());
      ms.erase(it);

      int cur_cost = Y[x];
      int cur_num = 1;
      ckmin(cost[cur_num], cur_cost);
      for (auto co: ms) {
        cur_cost += co;
        cur_num++;
        ckmin(cost[cur_num], cur_cost);
      }

      ms.insert(X[x]);
    }
    // cout << i << ": " << cost << endl;

    // update its own dp
    for (int j = n; j >= 0; j--) {
      if (dp[i][j] == INF) continue;
      for (int k = m; k >= 0; k--) {
        ckmin(dp[i][j+k], dp[i][j] + cost[k]);
      }
    }
    // update next
    for (int j: adj[i]) {
      for (int k = 0; k <= n; k++) {
        if (dp[i][k] == INF) break;
        ckmin(dp[j][k], dp[i][k]);
      }
    }
  }

  vector<int> ans(n+1, INF);
  for (int i = 0; i < c; i++) {
    for (int j = 0; j <= n; j++) {
      ckmin(ans[j], dp[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (ans[i] < INF) {
      cout << ans[i] << '\n';
    }
    else break;
  }
}
