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

const int maxn = 1005;
int cnt[maxn][maxn];
int n;
bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < n && !cnt[i][j];
}
void fillLeft(int i, int j) {
  if (!valid(i, j)) return;
  cnt[i][j] = cnt[i+1][j] = 1;
  fillLeft(i-2, j-2);
  fillLeft(i+2, j-2);
}
void fillRight(int i, int j) {
  if (!valid(i, j)) return;
  cnt[i][j] = cnt[i+1][j] = 1;
  fillRight(i-2, j+2);
  fillRight(i+2, j+2);
}
void fillUp(int i, int j) {
  if (!valid(i, j)) return;
  cnt[i][j] = cnt[i][j+1] = 1;
  fillUp(i-2, j-2);
  fillUp(i-2, j+2);
}
void fillDown(int i, int j) {
  if (!valid(i, j)) return;
  cnt[i][j] = cnt[i][j+1] = 1;
  fillDown(i+2, j-2);
  fillDown(i+2, j+2);
}
int solve() {
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  F0R(i, n) {
    F0R(j, n) {
      cnt[i][j] = 0;
      cin >> a[i][j];
    }
  }
  if (n % 4 == 2) {
    fillLeft(n/2-1, n/2-1);
    fillRight(n/2-1, n/2+2);
    fillUp(n/2-3, n/2);
    fillDown(n/2+2, n/2);
  }
  else {
    fillLeft(n/2-1-1, n/2-1-1);
    fillRight(n/2-1-1, n/2+2-1);
    fillUp(n/2-3-1, n/2-1);
    fillDown(n/2+2-1, n/2-1);
  }

  int ans = 0;
  F0R(i, n) {
    F0R(j, n) {
      if (cnt[i][j]) ans ^= a[i][j];
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
