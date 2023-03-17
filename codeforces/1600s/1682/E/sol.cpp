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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<int> P(N);
  F0R(i, N) {
    cin >> P[i];
    P[i]--;
  }

  vector<vector<int>> adj(N);
  map<pair<int, int>, int> id;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
    id[{a, b}] = id[{b, a}] = i;
  }

  vector<bool> vis(N, false);
  auto dfs = y_combinator([&](auto dfs, int i, vector<int>& cyc) -> void {
    vis[i] = 1;
    cyc.push_back(i);
    if (!vis[P[i]]) dfs(P[i], cyc);
  });

  vector<int> order(N);
  vector<vector<int>> g(M);
  vector<int> indegree(M);
  F0R(i, N) {
    if (!vis[i]) {
      vector<int> cyc;
      dfs(i, cyc);
      F0R(j, sz(cyc)) order[cyc[j]] = j;

      vector<int> v;
      for (auto j: cyc) {
        sort(all(adj[j]), [&](int a, int b) {
          a = order[a], b = order[b];
          if (a < order[j]) a += N;
          if (b < order[j]) b += N;
          return a < b;
        });
        for (auto a: adj[j]) v.push_back(id[{j, a}]);
        for (int k = 0; k + 1 < sz(adj[j]); k++) {
          int a = id[{j, adj[j][k]}];
          int b = id[{j, adj[j][k+1]}];
          g[a].push_back(b);
          indegree[b]++;
        }
      }

      sort(all(v)); v.erase(unique(all(v)), v.end());
      queue<int> q;
      for (auto j: v) {
        if (!indegree[j]) q.push(j);
      }
      while (!q.empty()) {
        int f = q.front(); q.pop();
        cout << (f+1) << ' ';
        for (auto j: g[f]) {
          if (--indegree[j] == 0) {
            q.push(j);
          }
        }
      }
    }
  }
  cout << '\n';
}
