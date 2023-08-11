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

int ans[maxn];
bool take[maxn][2];

void recon(int i, int p, int took) {
  ans[i] = take[i][took] ? adj[i].size() : 1;
  for (int j: adj[i]) {
    if (j != p) {
      recon(j, i, take[i][took]);
    }
  }
}

array<int, 2> dp[maxn][2];
array<int, 2> dfs(int i, int p, int took) {
  if (dp[i][took][0] != -1) return dp[i][took];
  auto& res = dp[i][took];
  int t = 0, sum = 1;
  for (int j: adj[i]) {
    if (j != p) {
      auto [a, b] = dfs(j, i, 0);
      t += a, sum += b;
    }
  }

  if (!took) {
    int nt = 1, nsum = sz(adj[i]);
    for (int j: adj[i]) {
      if (j != p) {
        auto [a, b] = dfs(j, i, 1);
        nt += a, nsum += b;
      }
    }
    if (t > nt || (t == nt && sum < nsum)) {
      take[i][took] = 0;
      return res = {t, sum};
    }
    else {
      take[i][took] = 1;
      return res = {nt, nsum};
    }
  }
  else return res = {t, sum};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  if (N == 2) {
    cout << "2 2\n";
    cout << "1 1\n";
    return 0;
  }
  memset(dp, -1, sizeof dp);
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto [t, sum] = dfs(1, 1, 0);
  recon(1, 1, 0);

  cout << t << ' ' << sum << '\n';
  FOR(i, 1, N+1) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
