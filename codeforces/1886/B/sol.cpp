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

double solve() {
  pair<int, int> P; cin >> P.first >> P.second;
  pair<int, int> A; cin >> A.first >> A.second;
  pair<int, int> B; cin >> B.first >> B.second;
  pair<int, int> O = {0, 0};

  auto in = [&](pair<int, int> a, pair<int, int> b, double r) -> bool {
    return hypot(a.first - b.first, a.second - b.second) <= r;
  };


  double lo = 0, hi = 1e4+4;
  REP(200) {
    double mid = (lo + hi) / 2;
    bool poss = false;
    poss |= in(O, A, mid) && in(A, P, mid);
    poss |= in(O, A, mid) && in(A, B, 2*mid) && in(B, P, mid);

    poss |= in(O, B, mid) && in(B, P, mid);
    poss |= in(O, B, mid) && in(B, A, 2*mid) && in(A, P, mid);

    if (poss) hi = mid;
    else lo = mid;
  }

  return hi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  cout << fixed << setprecision(10);
  while (T--) cout << solve() << '\n';
}
