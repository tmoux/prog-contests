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

const int maxn = 2e5+5;
int N;
vector<int> adj[maxn];

int sub[maxn];

void dfsSize(int i, int p) {
  sub[i] = 1;
  pair<int, int> heavy = {-1, -1};
  F0R(idx, sz(adj[i])) {
    int j = adj[i][idx];
    if (j == p) continue;
    dfsSize(j, i);
    sub[i] += sub[j];
    ckmax(heavy, {sub[j], idx});
  }
  if (heavy.second != -1) {
    swap(adj[i][0], adj[i][heavy.second]);
  }
}

const int MX = 260;
struct S {
  array<vector<int>, 2> dp;

  int getMin() {
    int res = 1e9;
    F0R(d, 2) {
      FOR(i, 1, sz(dp[d])) {
        ckmin(res, dp[d][i]);
      }
    }
    return res;
  }

  friend ostream &operator<<(ostream &os, const S &p) {
    return os << p.dp[0] << ' ' << p.dp[1];
  }
};

int calc(int k, int d) {
  return d == 1 ? k*k : k*k-k*(k+1)/2;
}

S init(int s) {
  S res;
  F0R(d, 2) res.dp[d].resize(s+1, 1e9);
  if (s == 1) {
    F0R(d, 2) res.dp[d][1] = calc(1, d);
  }
  return res;
}

S merge(S a, S b) {
  int sa = sz(a.dp[0])-1;
  int sb = sz(b.dp[0])-1;
  S res = init(min(MX, sa + sb));
  F0R(d, 2) {
    FOR(i, 1, min(sa, MX)+1) {
      FOR(j, 1, min(sb, MX)+1) {
        if (i+j <= min(MX, sa+sb)) {
          ckmin(res.dp[d][i+j], a.dp[d][i] + b.dp[d][j] - calc(i, d) - calc(j, d) + calc(i+j, d));
          ckmin(res.dp[d][i], a.dp[d][i] + b.dp[d^1][j]);
        }
      }
    }
  }
  return res;
}

S dfs(int i, int p) {
  S res;
  bool hasInit = false;
  for (int j: adj[i]) {
    if (j == p) continue;
    S tmp = dfs(j, i);
    if (!hasInit) {
      res = init(1);
      hasInit = 1;
    }
    res = merge(res, tmp);
  }
  if (!hasInit) {
    res = init(1);
    hasInit = 1;
  }
  return res;
}

void solve() {
  cin >> N;
  F0R(i, N) {
    adj[i].clear();
  }
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  // dfsSize(0, 0);
  S ans = dfs(0, 0);
  cout << 1LL * N * N - ans.getMin() << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
