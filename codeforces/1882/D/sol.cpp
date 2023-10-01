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
int N, A[maxn];
vector<int> adj[maxn];

int sub_size[maxn];
ll dp[maxn];
ll ans[maxn];
void dfs(int i, int p) {
  sub_size[i] = 1;
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    sub_size[i] += sub_size[j];
    dp[i] += dp[j];
  }
  if (i != p) {
    dp[i] += 1LL * (A[i] ^ A[p]) * sub_size[i];
  }
  // cout << i+1 << ": " << dp[i] << endl;
}

void reroot(int i, int p, ll cur, int cur_size) {
  ans[i] = dp[i] - 1LL * (A[i] ^ A[p]) * sub_size[i];
  if (i != p) ans[i] += 1LL * (A[i] ^ A[p]) * cur_size + cur;

  for (int j: adj[i]) {
    if (j == p) continue;
    reroot(j, i, ans[i] - dp[j], N - sub_size[j]);
  }
}

void solve() {
  cin >> N;
  F0R(i, N) cin >> A[i];
  REP(N-1) {
    int u, v; cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(0, 0);
  reroot(0, 0, 0, 0);

  F0R(i, N) {
    cout << ans[i] << " \n"[i == N-1];
  }

  F0R(i, N) {
    adj[i].clear();
    sub_size[i] = dp[i] = 0;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
