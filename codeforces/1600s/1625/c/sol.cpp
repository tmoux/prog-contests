#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

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

const int maxn = 505;

int n, l, k;
int d[maxn];
int a[maxn];

const int INF = 2e9;
int dp[2][maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> l >> k;
  F0R(i, n) {
    cin >> d[i];
  }
  d[n] = l;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int j = 0; j <= n; j++) {
    for (int c = 0; c < n; c++) {
      if (j >= n-k) {
        dp[0][j][c] = 0;
      }
      else dp[0][j][c] = INF;
    }
  }
  for (int i = n-1; i >= 1; i--) {
    for (int j = 0; j <= n; j++) {
      for (int c = 0; c < n; c++) {
        int dist = d[i+1] - d[i];
        dp[1][j][c] = min(dp[0][j+1][i] + dist * a[i],
                          dp[0][j][c] + dist * a[c]);
      }
    }
    swap(dp[0], dp[1]);
  }
  int ans = dp[0][1][0] + (d[1] - d[0]) * a[0];
  cout << ans << '\n';
}
