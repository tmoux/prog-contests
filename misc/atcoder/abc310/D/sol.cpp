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

const int maxn = 10;
int N, T, M;
int dp[maxn+1][1 << maxn];

bool bad[maxn][maxn];

vector<int> masks;

int f(int t, int mask) {
  if (t > T) return 0;
  int& res = dp[t][mask];
  if (res != -1) return res;
  if (mask == (1 << N) - 1) {
    return res = t == T ? 1 : 0;
  }
  res = 0;
  for (int nmask: masks) {
    if ((mask & nmask) == 0) {
      res += f(t+1, mask | nmask);
    }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> T >> M;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    bad[a][b] = bad[b][a] = 1;
  }
  memset(dp, -1, sizeof dp);

  FOR(mask, 1, 1 << N) {
    bool poss = true;
    F0R(i, N) {
      if (mask & (1 << i)) {
        F0R(j, N) {
          if (mask & (1 << j)) {
            if (bad[i][j]) {
              poss = false;
              break;
            }
          }
        }
      }
    }
    if (poss) masks.push_back(mask);
  }

  int ans = f(0, 0);
  // DEBUG(ans);
  int fac = 1;
  FOR(i, 1, T+1) fac *= i;

  cout << (ans / fac) << '\n';
}
