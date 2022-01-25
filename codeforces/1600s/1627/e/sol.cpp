#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
  ostream& operator<<(ostream &os, const T_container &v) { 
    os << '['; string sep; 
    for (const T &x : v) 
      os << sep << x, sep = ", "; 
    return os << ']'; 
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

struct Edge {
  int to;
  ll weight;
};
const ll INF = -1e18;

template<class T>
using rev_pq = priority_queue<T,vector<T>,greater<T>>;

void solve() {
  int n, m, k, cnt = 1, a, b, c, d, h, e;
  cin >> n >> m >> k;
  int t[n + 1];
  vector<ll> dp(k * 2 + 3, INF);
  vector<array<int, 2>> to(k * 2 + 3);
  vector<vector<array<int, 2>>> row(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> t[i];
  row[1].push_back({1, cnt++});
  dp[1] = 0;
  while (k--) {
    cin >> a >> b >> c >> d >> h;
    dp[cnt] = INF;
    row[a].push_back({b, cnt++});
    dp[cnt] = INF;
    row[c].push_back({d, cnt++});
    to[cnt - 2] = {cnt - 1, h};
  }
  dp[cnt] = INF;
  row[n].push_back({m, cnt});
  for (int i = 1; i <= n; ++i) {
    e = row[i].size();
    sort(row[i].begin(), row[i].end());
    for (int j = 1; j < e; ++j)
      dp[row[i][j][1]] = max(dp[row[i][j][1]], dp[row[i][j - 1][1]] + 1LL * t[i] * (row[i][j - 1][0] - row[i][j][0]));
    for (int j = e - 2; j >= 0; --j)
      dp[row[i][j][1]] = max(dp[row[i][j][1]], dp[row[i][j + 1][1]] + 1LL * t[i] * (row[i][j][0] - row[i][j + 1][0]));
    for (auto j : row[i])
      if (to[j[1]][0] && dp[j[1]] != INF)
        dp[to[j[1]][0]] = max(dp[to[j[1]][0]], dp[j[1]] + to[j[1]][1]);
  }
  if (dp[cnt] == INF)
    cout << "NO ESCAPE\n";
  else
    cout << - dp[cnt] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
