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

int limit, numQueries;
int ask(int i, int j, int k) {
  numQueries++;
  assert(numQueries <= limit);

  assert(i != j && j != k && i != k);

  printf("? %d %d %d\n", i, j, k);
  fflush(stdout);
  int x; cin >> x;
  assert(x != -1);
  return x;
}

void answer(int i, int j) {
  printf("! %d %d\n", i, j);
  fflush(stdout);
}

void solve() {
  int n; cin >> n;
  limit = 2*n-2;
  numQueries = 0;

  int i1 = 1, i2 = 2, i3 = 3;
  int curD = ask(i1, i2, i3);
  for (int i = 4; i <= n; i++) {
    int d1 = ask(i1, i2, i);
    int d2 = ask(i2, i3, i);
    if (d1 > curD && d1 > d2) {
      // throw out i3
      i3 = i;
      curD = d1;
    }
    else if (d2 > curD && d2 >= d1) {
      // throw out i1
      i1 = i;
      curD = d2;
    }
  }
  int j = -1;
  for (int i = 1; i <= n; i++) {
    if (i != i1 && i != i2 && i != i3) {
      j = i;
      break;
    }
  }
  pair<int,int> guess = {-1, -1};
  int d1 = ask(i1, i2, j);
  int d2 = ask(i2, i3, j);
  int d3 = ask(i1, i3, j);
  if (d1 < d2 && d1 < d3 && d1 == d3) {
    guess = {i3, i3};
  }
  else if (d2 < d1 && d2 < d3 && d1 == d3) {
    guess = {i1, i1};
  }
  else if (d3 < d1 && d3 < d2 && d1 == d3) {
    guess = {i2, i2};
  }
  else {
    if (curD == d1) guess = {i1, i2};
    else if (curD == d2) guess = {i2, i3};
    else if (curD == d3) guess = {i1, i3};
  }
  answer(guess.first, guess.second);
}

int main() {
  int t; cin >> t;
  while (t--) solve();
}
