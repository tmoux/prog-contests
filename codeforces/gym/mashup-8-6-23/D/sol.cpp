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

const int MX = 30;
int A[MX], B[MX];

ll dp[MX][2][2];
ll F(int i, bool isLtA, bool isLtB) {
  if (i < 0) return 1;
  auto& res = dp[i][isLtA][isLtB];
  if (res != -1) return res;
  res = 0;
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      if (x == 1 && y == 1) continue;
      if ((isLtA || (x <= A[i])) &&
          (isLtB || (y <= B[i]))) {
        res += F(i-1, isLtA || (x < A[i]), isLtB || (y < B[i]));
      }
    }
  }
  return res;
}

ll getsum(int a, int b) {
  if (a < 0 || b < 0) return 0;
  F0R(i, MX) {
    A[i] = (a >> i) & 1;
    B[i] = (b >> i) & 1;
  }
  memset(dp, -1, sizeof dp);
  return F(MX-1, 0, 0);
}

ll solve() {
  ll L, R; cin >> L >> R;
  ll ans = getsum(R, R);
  ans -= getsum(L-1, R);
  ans -= getsum(R, L-1);
  ans += getsum(L-1, L-1);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
