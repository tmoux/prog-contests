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

// dp[i][2] = min cost of subtree i:
// 0 = increasing, 1 = decreasing
// Note: dp[i][t] doesn't make any assumptions about height of parent.
// Merge as many increasing and decreasing together as possible (greedy fashion)
// For continuing an increasing path, take one (biggest cost to swap) and do the
// same calculation without it.
// Continuing a decreasing path is analogous.

const int maxn = 2e5+5;

int T[maxn], H[maxn];
int N;
vector<int> adj[maxn];
ll dp[maxn][2];

void dfs(int i, int p) {
  vector<int> childs;
  for (int j: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    childs.push_back(j);
  }
  const ll INF = 1e18;
  dp[i][0] = dp[i][1] = INF;
  if (childs.empty()) {
    dp[i][0] = dp[i][1] = T[i];
  }
  else {
    auto calc = [&](deque<pair<ll, ll>> leq, deque<pair<ll, ll>> geq) -> ll {
      ll ans = 0;
      // Pair up < and >:
      while (sz(leq) > 0 && sz(geq) > 0) {
        ll x = leq.back().second; leq.pop_back();
        ll y = geq.back().second; geq.pop_back();
        ans += x + T[i] + y;
      }
      // Switch and pair up as long as it's beneficial:
      while (sz(leq) >= 2 && leq.front().first < T[i]) {
        ll x = leq.front().second + leq.front().first; leq.pop_front();
        ll y = leq.back().second; leq.pop_back();
        ans += x + T[i] + y;
      }
      while (!leq.empty()) {
        auto x = leq.back().second; leq.pop_back();
        ans += x + T[i];
      }
      while (sz(geq) >= 2 && geq.front().first < T[i]) {
        ll x = geq.front().second + geq.front().first; geq.pop_front();
        ll y = geq.back().second; geq.pop_back();
        ans += x + T[i] + y;
      }
      while (!geq.empty()) {
        auto x = geq.back().second; geq.pop_back();
        ans += x + T[i];
      }
      return ans;
    };

    deque<pair<ll, ll>> leq, geq; // cost to switch, cost
    for (int j: childs) {
      if (H[j] < H[i]) leq.emplace_back(INF, dp[j][0]);
      else if (H[j] > H[i]) geq.emplace_back(INF, dp[j][1]);
      else if (dp[j][0] <= dp[j][1]) leq.emplace_back(dp[j][1] - dp[j][0], dp[j][0]);
      else if (dp[j][0] > dp[j][1]) geq.emplace_back(dp[j][0] - dp[j][1], dp[j][1]);
      else assert(false);
    }
    sort(all(leq)); sort(all(geq));

    ll end_all = calc(leq, geq) + (i != p ? T[i] : 0);
    ckmin(dp[i][0], end_all);
    ckmin(dp[i][1], end_all);

    // Try keep increasing:
    {
      auto nleq = leq, ngeq = geq;
      ll keep_inc = INF;
      if (!nleq.empty()) {
        auto p = nleq.back(); nleq.pop_back();
        keep_inc = calc(nleq, ngeq) + p.second + T[i];
      }
      else if (ngeq.front().first < INF) {
        auto p = ngeq.front(); ngeq.pop_front();
        keep_inc = calc(nleq, ngeq) + p.second + p.first + T[i];
      }
      ckmin(dp[i][0], keep_inc);
    }
    // Try keep decreasing:
    {
      auto nleq = leq, ngeq = geq;
      ll keep_dec = INF;
      if (!ngeq.empty()) {
        auto p = ngeq.back(); ngeq.pop_back();
        keep_dec = calc(nleq, ngeq) + p.second + T[i];
      }
      else if (nleq.front().first < INF) {
        auto p = nleq.front(); nleq.pop_front();
        keep_dec = calc(nleq, ngeq) + p.second + p.first + T[i];
      }
      ckmin(dp[i][1], keep_dec);
    }
  };
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  FOR(i, 1, N+1) cin >> T[i];
  FOR(i, 1, N+1) cin >> H[i];
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 1);
  cout << min(dp[1][0], dp[1][1]) << '\n';
}
