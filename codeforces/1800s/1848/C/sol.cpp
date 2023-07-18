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

bool solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  F0R(i, N) cin >> A[i];
  F0R(i, N) cin >> B[i];

  // REP(20) {
  //   cout << A << endl;
  //   vector<int> C(N);
  //   F0R(i, N) C[i] = abs(A[i] - B[i]);
  //   A = B;
  //   B = C;
  // }
  // return false;

  int par = -1;
  F0R(i, N) {
    if (A[i] == 0 && B[i] == 0) continue;
    int p = 0;
    if (A[i] == 0) p = 0;
    else if (B[i] == 0) p = 1;
    else if (A[i] >= B[i]) {
      int turns = (A[i] - B[i]) / (2 * B[i]);
      A[i] -= turns * 2 * B[i];
      // p = turns&1;
      while (A[i] != 0) {
        p = (p + 1) % 3;
        int c = abs(A[i] - B[i]);
        A[i] = B[i];
        B[i] = c;
      }
    }
    else {
      int turns = (B[i] - A[i]) / (2 * A[i]);
      B[i] -= turns * 2 * A[i];
      // p = turns&1;
      while (A[i] != 0) {
        p = (p + 1) % 3;
        int c = abs(A[i] - B[i]);
        A[i] = B[i];
        B[i] = c;
      }
    }
    //  cout << i << ": " << p << endl;
    // DEBUG(p);
    assert(p != -1);
    if (par == -1) par = p;
    else if (par != p) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}
