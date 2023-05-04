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

const int maxn = 1e5+5;
int N;
vector<int> adj[maxn];

pair<int, int> mx;
int A, B;

void dfs(int i, int p, int d) {
  ckmax(mx, {d, i});
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs(j, i, d+1);
  }
}

struct DSU {
  int n;
  vector<int> par;
  int comps;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
    comps = n;
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    comps--;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  int getComps() {
    return comps;
  }
};

vector<pair<int, int>> edges[maxn];
void dfs2(int i, int p, int o, int d) {
  if (d > 0) {
    edges[d].emplace_back(i, o);
  }
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs2(j, i, o, d+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  mx = {-1, -1};
  dfs(0, 0, 0);
  A = mx.second;
  mx = {-1, -1};
  dfs(A, A, 0);
  B = mx.second;

  dfs2(A, A, A, 0);
  dfs2(B, B, B, 0);

  vector<int> ans;
  DSU dsu(N);
  for (int i = N; i >= 1; i--) {
    for (auto [a, b]: edges[i]) {
      dsu.Union(a, b);
    }
    ans.push_back(dsu.getComps());
  }
  reverse(all(ans));
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}
