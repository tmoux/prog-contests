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
  int N; cin >> N;
  vector<vector<bool>> adj(N, vector<bool>(N));
  vector<int> degree(N, 0);
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, N) {
      adj[i][j] = s[j] - '0';
      if (adj[i][j]) degree[i]++;
    }
  }

  vector<bool> vis(N, false);

  auto dfs = y_combinator([&](auto dfs, int i, vector<int>& comp) -> void {
    comp.push_back(i);
    vis[i] = true;
    F0R(j, N) {
      if (adj[i][j] && !vis[j]) {
        dfs(j, comp);
      }
    }
  });

  vector<vector<int>> comps;
  F0R(i, N) {
    if (!vis[i]) {
      vector<int> comp;
      dfs(i, comp);
      comps.push_back(comp);
    }
  }

  if (sz(comps) == 1) {
    cout << 0 << '\n';
  }
  else {
    pair<int, vector<int>> smallest = {N+1, {}};
    for (auto comp: comps) {
      ckmin(smallest, {sz(comp), comp});
      sort(all(comp), [&](int i, int j) {
          return degree[i] < degree[j];
          });
      int x = -1;
      if (sz(comp) == 1 || (degree[comp[0]] < sz(comp) - 1)) x = comp[0];
      if (x != -1) {
        cout << 1 << '\n';
        cout << x+1 << '\n';
        return;
      }
    }

    // if there are >= 3 components: then can always do 2
    if (sz(comps) >= 3) {
      int a = comps[0][0] + 1;
      int b = comps[1][0] + 1;
      cout << 2 << '\n';
      cout << a << ' ' << b << '\n';
      return;
    }

    // assume each is a clique, output smallest one
    cout << smallest.first << '\n';
    for (int x: smallest.second) {
      cout << x + 1 << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
