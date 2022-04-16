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

const int maxn = 12;
const int maxx = 6000;

vector<int> states[maxx];
array<int, 3> val[maxx];
int pt = 0;

void dfs(vector<int> v, int a, int b, int c) {
  if (a > 3 || b > 3 || c > 3 || a+b+c > 9) return;
  val[pt] = {a, b, c};
  states[pt++] = v;

  v.push_back(0);
  dfs(v, a+1, b, c);
  v.pop_back();

  v.push_back(1);
  dfs(v, a, b+1, c);
  v.pop_back();

  v.push_back(2);
  dfs(v, a, b, c+1);
  v.pop_back();
}

int dp[maxn][maxx];
int X[maxn][maxn];

int E, W;
int f(int i, int state) {
  if (i == E) return 0;
  int& res = dp[i][state];
  if (res != -1) return res;

  res = 1e9;
  F0R(j, pt) {
    if (val[j][0] == X[i][0] && 
        val[j][1] == X[i][1] &&
        val[j][2] == X[i][2]) {
      int k = 0;
      auto& u = states[state];
      auto& v = states[j];
      while (k < sz(u) && k < sz(v) && u[k] == v[k]) k++;
      int cost = (sz(u) - k) + (sz(v) - k);
      ckmin(res, cost + f(i+1, j));
    }
  }
  assert(res < 1e9);
  return res;
}

void solve() {
  cin >> E >> W;
  memset(X, 0, sizeof X);
  memset(dp, -1, sizeof dp);
  F0R(i, E) {
    F0R(j, W) {
      cin >> X[i][j];
    }
  }
  int ans = f(0, 0);
  F0R(j, W) ans += X[E-1][j];
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  dfs({}, 0, 0, 0);

  int T; cin >> T;
  FOR(tt, 1, T+1) {
    cout << "Case #" << tt << ": ";
    solve();
  }
}
