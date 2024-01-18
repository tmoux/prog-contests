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

/*
** Brute force order (012...210)
** Fix middle element: greedily pick max on left/right side
 */

int solve() {
  int N; cin >> N;
  vector<vector<int>> A(N, vector<int>(3));
  F0R(j, 3) {
    F0R(i, N) {
      cin >> A[i][j];
    }
  }
  vector<int> p(3); iota(all(p), 0);

  vector<vector<int>> pfx = A;
  FOR(i, 1, N) {
    F0R(j, 3) {
      ckmax(pfx[i][j], pfx[i-1][j]);
    }
  }
  vector<vector<int>> sfx = A;
  for (int i = N-2; i >= 0; i--) {
    F0R(j, 3) {
      ckmax(sfx[i][j], sfx[i+1][j]);
    }
  }

  int ans = 0;
  do {
    for (int i = 1; i < N-1; i++) {
      ckmax(ans, pfx[i-1][p[0]] + A[i][p[1]] + sfx[i+1][p[2]]);
    }
  } while (next_permutation(all(p)));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
