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

const int maxn = 105;
const int INF = 2e9;
const int MX = 100 * 100 + 50;

int n;
int a[maxn], b[maxn], sum_ab[maxn];

int dp[maxn][MX];

int f(int i, int asum) {
  if (i == n) return 0;
  int& res = dp[i][asum];
  if (res != -1) return res;

  int bsum = i == 0 ? 0 : sum_ab[i-1] - asum;
  // don't swap
  res = asum * a[i] + bsum * b[i] + f(i+1, asum + a[i]);
  // do swap
  ckmin(res, asum * b[i] + bsum * a[i] + f(i+1, asum + b[i]));
  return res;
}

void solve() {
  cin >> n;
  F0R(i, n) cin >> a[i];
  F0R(i, n) cin >> b[i];
  F0R(i, n) {
    sum_ab[i] = a[i] + b[i];
    if (i > 0) sum_ab[i] += sum_ab[i-1];
  }

  F0R(i, n) {
    F0R(j, MX) dp[i][j] = -1;
  }
  int ans = 0;
  F0R(i, n) {
    ans += (n-1) * a[i] * a[i];
    ans += (n-1) * b[i] * b[i];
  }
  int add = 2 * f(0, 0);
  ans += add;
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}