#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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
int N, Q, A[maxn];

gp_hash_table<int, ll> dp[maxn];
vector<int> adj[maxn];
int par[maxn], depth[maxn];

ll H[maxn];
void dfs(int i) {
  depth[i] = depth[par[i]] + 1;
  H[i] = 1LL * A[i] * A[i] + H[par[i]];
  for (int j: adj[i]) {
    dfs(j);
  }
}

const int K = 10;
ll f(int x, int y) {
  if (x == y) return H[x];
  if (x > y) swap(x, y);
  // if (dp[x].count(y)) return dp[x][y];
  int d = depth[x];
  if (d % K == 0) {
    if (dp[x].find(y) != dp[x].end()) {
      return dp[x][y];
    }
    else return dp[x][y] = 1LL * A[x] * A[y] + f(par[x], par[y]);
  }
  else return 1LL * A[x] * A[y] + f(par[x], par[y]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  FOR(i, 1, N+1) {
    cin >> A[i];
  }

  FOR(i, 2, N+1) {
    cin >> par[i];
    adj[par[i]].push_back(i);
  }
  dfs(1);

  F0R(i, Q) {
    int x, y; cin >> x >> y;
    cout << f(x, y) << '\n';
  }
}
