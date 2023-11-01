#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

ll solve() {
  int N; cin >> N;
  int K; cin >> K;
  vector<int> S(N); for (auto& x: S) cin >> x;
  vector<vector<int>> adj(N);
  REP(N-1) {
    int a, b; cin >> a >> b; a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  ll total = std::accumulate(all(S), 0LL);
  vector<ll> sub(N); // answer for subtree i
  vector<ll> sumS(N); // sum of S in the subtree

  y_combinator([&](auto dfs, int i, int p) -> void {
    sumS[i] = S[i];
    for (int j: adj[i]) {
      if (j == p) continue;
      dfs(j, i);
      sumS[i] += sumS[j];
      sub[i] += sub[j] + sumS[j];
    }
  })(0, 0);

  vector<ll> ans(N);
  y_combinator([&](auto dfs, int i, int p, ll parAns) -> void {
    ans[i] = sub[i] + parAns;
    for (int j: adj[i]) {
      if (j == p) continue;
      ll newParAns = ans[i] - (sub[j] + sumS[j]) + (total - sumS[j]);
      dfs(j, i, newParAns);
    }
  })(0, 0, 0);
  // DEBUG(sub);
  // DEBUG(ans);
  sort(all(ans));
  return ans[K-1];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
