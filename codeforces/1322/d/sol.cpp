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

const int maxn = 2005, INF = 1e9;

int L[maxn], S[maxn], C[2*maxn];
int dp[2*maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  F0R(i, n) cin >> L[i];
  F0R(i, n) cin >> S[i];
  FOR(i, 1, n+m+1) cin >> C[i];

  F0R(i, 2*maxn) FOR(j, 1, maxn) dp[i][j] = -INF;

  F0Rd(i, n) {
    for (int j = n; j >= 1; j--) {
      ckmax(dp[L[i]][j], dp[L[i]][j-1] - S[i] + C[L[i]]);
    }
    for (int j = L[i]; j <= n+m; j++) {
      for (int k = 0; k <= n >> (j-L[i]); k++) {
        ckmax(dp[j+1][k/2], dp[j][k] + (k/2)*C[j+1]);
      }
    }
  }

  int ans = 0;
  F0R(i, n+m+1) ckmax(ans, dp[i][0]);
  cout << ans << '\n';
}
