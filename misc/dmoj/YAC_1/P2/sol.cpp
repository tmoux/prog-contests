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

const int maxn = 2e5+5;
int N;
bool isb[maxn];
vector<int> adj[maxn];

ll ans = 0;
ll dp[maxn][3][3]; // # paths with b black, w white

void dfs(int i, int p) {
  int ib = isb[i] ? 1 : 0;
  int iw = isb[i] ? 0 : 1;
  dp[i][ib][iw] = 1;
  ans++;

  for (int j: adj[i]) if (j != p) {
    dfs(j, i);
    F0R(b1, 3) F0R(w1, 3) F0R(b2, 3) F0R(w2, 3) {
      if (b1 + b2 < 3 && w1 + w2 < 3) {
        ans += dp[i][b1][w1] * dp[j][b2][w2];
      }
    }

    F0R(b, 3) F0R(w, 3) {
      if (b + ib < 3 && w + iw < 3) {
        dp[i][b+ib][w+iw] += dp[j][b][w];
      }
    }
  }

  /*
  F0R(b, 3) F0R(w, 3) {
    cout << i << ' ' << b << ' ' << w << ": " << dp[i][b][w] << '\n';
  }
  cout << "curans: " << ans << endl;
  cout << '\n';
  */
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  string s; cin >> s;
  for (int i = 1; i <= N; i++) {
    isb[i] = s[i-1] == 'B'; 
  }
  REP(N-1) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0);

  ans = 1LL * N * (N+1) / 2 - ans;
  cout << ans << '\n';
}
