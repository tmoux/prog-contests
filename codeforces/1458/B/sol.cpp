#pragma GCC optimize("O3,unroll-loops")

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

const int maxn = 102;

const int OFF = 2*maxn*maxn;
int dp[2][maxn][2*2*maxn*maxn]; // only counts for sure excess
int N, A[maxn], B[maxn];

bool ok(int x) {
  return -200*N <= x && x <= 200*N;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i] >> B[i];
    A[i] *= 2, B[i] *= 2;
  }

  for (int k = 0; k <= N; k++) {
    for (int e = -200*N; e <= 200*N; e++) {
      dp[0][k][e + OFF] = -2e9;
      dp[1][k][e + OFF] = -2e9;
    }
  }
  dp[0][0][0 + OFF] = 0;

  F0R(i, N) {
    for (int k = 0; k <= N; k++) {
      for (int e = -200*N; e <= 200*N; e++) {
        if (dp[0][k][e + OFF] == -2e9) continue;
        // Option 1: don't take it
        int d = B[i] / 2;
        if (ok(e - d))
          ckmax(dp[1][k][e - d + OFF], dp[0][k][e + OFF] + (e <= 0 ? 0 : min(e, d)));
        // Option 2: take it, increment k, add to excess
        if (ok(e + (A[i] - B[i])))
          ckmax(dp[1][k+1][e + (A[i] - B[i]) + OFF], dp[0][k][e + OFF] + B[i] + (e >= 0 ? 0 : min(-e, A[i] - B[i])));
      }
    }
    for (int k = 0; k <= N; k++) {
      for (int e = -200*N; e <= 200*N; e++) {
        dp[0][k][e + OFF] = dp[1][k][e + OFF];
        dp[1][k][e + OFF] = -2e9;
      }
    }
  }

  // Output answer, dividing by 2.
  cout << fixed << setprecision(5);
  FOR(k, 1, N+1) {
    int ans = 0;
    for (int e = -200*N; e <= 200*N; e++) {
      ckmax(ans, dp[0][k][e + OFF]);
    }
    cout << ans / 2.0 << " \n"[k == N];
  }
}
