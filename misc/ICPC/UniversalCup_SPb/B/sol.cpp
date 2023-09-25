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

int isLeap(int x) {
  return x % 4 == 0;
}

int numDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getNumDays(int m, int y) {
  if (isLeap(y) && m == 1) return 29;
  else return numDays[m];
}

map<int, int> startDay;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int Y = 1970;
  int cur = 3;
  while (Y <= 2037) {
    startDay[Y] = cur;
    cur = (cur + 1) % 7;
    if (Y % 4 == 0) cur = (cur + 1) % 7;
    Y++;
  }

  int y; cin >> y;
  cur = startDay[y];

  int ans = 0;
  for (int m = 0; m < 12; m++) {
    // cout << m << ": " << (cur + getNumDays(m, y) + 7-1) / 7 << endl;
    ans += (cur + getNumDays(m, y) + 7-1) / 7;
    cur = (cur + getNumDays(m, y)) % 7;
  }
  cout << ans << '\n';
}
