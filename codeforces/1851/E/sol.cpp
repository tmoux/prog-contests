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

void solve() {
  int N, K; cin >> N >> K;
  vector<ll> C(N+1);
  FOR(i, 1, N+1) cin >> C[i];
  vector<ll> dp = C;
  REP(K) {
    int i; cin >> i;
    dp[i] = 0;
  }

  vector<vector<int>> adj(N+1);
  vector<vector<int>> radj(N+1);
  vector<int> indegree(N+1);
  FOR(i, 1, N+1) {
    int m; cin >> m;
    REP(m) {
      indegree[i]++;
      int j; cin >> j;
      adj[j].push_back(i);
      radj[i].push_back(j);
      // cout << j << ' ' << i << endl;
    }
  }
  queue<int> q;
  FOR(i, 1, N+1) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }
  while (!q.empty()) {
    int i = q.front(); q.pop();
    if (!radj[i].empty()) {
      ll sum = 0;
      for (int j: radj[i]) sum += dp[j];
      ckmin(dp[i], sum);
    }
    // cout << i << ": " << radj[i] << endl;
    // cout << i << ": " << dp[i] << endl;
    for (int j: adj[i]) {
      if (--indegree[j] == 0) {
        q.push(j);
      }
    }
  }

  FOR(i, 1, N+1) {
    cout << dp[i] << " \n"[i == N];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
