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

/*
  Sum of all flows must be 0.
  We claim this is also a sufficient condition.
  We prove this by induction.
  Pick a spanning tree, all other edges will be 0.
  We can remove a leaf, set its parent edge, and then update its parent to maintain a sum of zero.
*/

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

const int maxn = 2e5+5;

int N, M, S[maxn];
vector<pair<int, int>> adj[maxn];
pair<int, int> edges[maxn];
int ans[maxn];

void dfs(int i, int p) {
  for (auto [j, ed]: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    if (S[j] != 0) {
      S[i] += S[j];
      ans[ed] = (i == edges[ed].first) ^ (S[j] < 0) ? abs(S[j]) : -abs(S[j]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> S[i];
  cin >> M;
  DSU dsu(N);
  F0R(i, M) {
    int x, y; cin >> x >> y;
    x--, y--;
    edges[i] = {x, y};
    if (dsu.Union(x, y)) {
      adj[x].emplace_back(y, i);
      adj[y].emplace_back(x, i);
    }
  }

  if (std::accumulate(S, S+N, 0LL) != 0) {
    cout << "Impossible\n";
    return 0;
  }
  dfs(0, 0);
  cout << "Possible\n";
  F0R(i, M) {
    cout << ans[i] << '\n';
  }
}
