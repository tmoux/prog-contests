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

void solve() {
  int N, X; cin >> N >> X;
  vector<int> ans;
  int rem = N % 4; if (rem == 0) rem = 4;
  int take = N - rem;
  int start = X <= 300000 ? 400000 : 100000;
  for (int x = start; x < start+take; x++) {
    ans.push_back(x);
  }
  if (rem == 1) {
    ans.push_back(X);
  }
  else if (rem == 2) {
    ans.push_back(X);
    ans.push_back(0);
  }
  else if (rem == 3) {
    if (X == 1) { // X = 1
      ans.push_back(3);
      ans.push_back(4);
      ans.push_back(6);
    }
    else if (X == 500000) {
      ans.push_back(499968);
      ans.push_back(1);
      ans.push_back(33);
    }
    else {
      ans.push_back(X^1);
      ans.push_back(1);
      ans.push_back(0);
    }
  }
  else if (rem == 4) {
    if (X > 3) {
      ans.push_back(X);
      ans.push_back(1);
      ans.push_back(2);
      ans.push_back(3);
    }
    else {
      ans.push_back(X);
      ans.push_back(4);
      ans.push_back(8);
      ans.push_back(12);
    }
  }

  assert(sz(ans) == N);
  assert(accumulate(all(ans), 0, bit_xor<int>()) == X);
  set<int> s; for (auto x: ans) s.insert(x); assert(sz(s) == N);
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
