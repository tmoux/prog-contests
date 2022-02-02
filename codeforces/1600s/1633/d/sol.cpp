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

const int maxn = 1e3+3;
const int INF = 1e9;
int steps[maxn];
void prep() {
  for (int i = 1; i <= 1000; i++) {
    steps[i] = INF;  
  }
  steps[1] = 0;
  for (int i = 1; i <= 1000; i++) {
    for (int x = 1; x <= i; x++) {
      if (i+i/x <= 1000) {
        ckmin(steps[i+i/x], steps[i]+1);
      }
    }
  }
  /*
  for (int i = 1; i <= 64; i++) {
    cout << i << ": " << steps[i] << endl;
  }
  */
}

void go(int n) {/*{{{*/
  set<int> cur = {1};
  F0R(i, n) {
    set<int> ncur = cur;
    for (int x: cur) {
      for (int i = 1; i <= x; i++) {
        ncur.insert(x+x/i);
      }
    }
    cur = ncur;
    cout << i << ": ";
    for (auto x: cur) {
      //bitset<6> b(x);
      //cout << b << ' ';
      cout << x << ' ';
    }
    cout << '\n';
  }
};/*}}}*/

int solve() {
  int n, k; cin >> n >> k;
  vector<int> b(n);
  for (auto& i: b) cin >> i;
  vector<int> c(n);
  for (auto& i: c) cin >> i;
  vector<int> cost(n);
  F0R(i, n) cost[i] = steps[b[i]];

  int B = min(15000, k);
  vector<int> dp(B+1, 0);
  F0R(i, n) {
    for (int j = B; j >= 0; j--) {
      if (j + cost[i] <= B) {
        ckmax(dp[j+cost[i]], dp[j] + c[i]);
      }
    }
  }
  int ans = *max_element(all(dp));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  prep();
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
