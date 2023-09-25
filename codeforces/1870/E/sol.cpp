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

int mex(vector<int> v) {
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) if (i != v[i]) return i;
  return sz(v);
}

int solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  int M = mex(A);
  if (M == 0) return 0;
  int k = 31 - __builtin_clz(M);
  int MX = 1 << (k+1);

  int MM = max(MX+5, *max_element(all(A)));

  vector<vector<int>> F(N, vector<int>(N));
  F0R(i, N) {
    vector<int> c(MM+1);
    int cur = 0;
    for (int j = i; j < N; j++) {
      c[A[j]] = 1;
      while (c[cur]) cur++;
      F[i][j] = cur;
    }
  }
  vector<vector<int>> ls(N);
  F0R(i, N) {
    ls[i].push_back(i);
    FOR(j, i+1, N) {
      if (F[i][j] > F[i][j-1] && F[i][j] > F[i+1][j]) {
        ls[j].push_back(i);
      }
    }
  }
  vector<vector<int>> dp(N+1, vector<int>(MX));
  dp[0][0] = 1;
  F0R(i, N) {
    F0R(j, MX) dp[i+1][j] |= dp[i][j];
    for (int l: ls[i]) {
      F0R(j, MX) {
        dp[i+1][j ^ F[l][i]] |= dp[l][j];
      }
    }
  }

  int ans = 0;
  F0R(j, MX) {
    if (dp[N][j]) ans = j;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
