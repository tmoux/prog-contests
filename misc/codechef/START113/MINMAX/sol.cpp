#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

int solve(int X, int Y) {
  if (X <= Y + 1) return 1;
  else if (X >= 2 * Y + 3) return (X - (2*Y+3) + 3);
  else return 2;
  /*
  auto mss = [&](const vector<int>& v) {
    int mn = 0, cur = 0;
    int ans = 0;
    for (auto x: v) {
      cur += x;
      ckmax(ans, cur - mn);
      ckmin(mn, cur);
    }
    return ans;
  };

  int N = X + Y;
  vector<int> v(N);
  int ans = 1e9;
  F0R(mask, 1 << N) {
    if (__builtin_popcount(mask) == X) {
      F0R(i, N) {
        v[i] = (mask & (1 << i)) ? 1 : -2;
      }
      ckmin(ans, mss(v));
    }
  }
  return ans;
  */
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // FOR(i, 1, 12) {
  //   FOR(j, 1, 12) {
  //     cout << solve(i, j) << ' ';
  //   }
  //   cout << endl;
  // }
  // return 0;
  int T; cin >> T;
  while (T--) {
    int X, Y; cin >> X >> Y;
    cout << solve(X, Y) << '\n';
  }
}
