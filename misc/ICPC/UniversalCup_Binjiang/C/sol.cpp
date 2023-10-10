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

const int maxn = 1005, MOD = 1e9+7;
int N, M, A[maxn][maxn];
vector<int> adj[maxn];
bool blocked[maxn];

const int MAX = 24;
int intersect[1 << MAX], can[1 << MAX];

int dp[1 << 20];

ll solve(int i) {
  vector<int> v;
  for (int j: adj[i]) {
    if (!blocked[j]) v.push_back(j);
  }
  int D = sz(v);

  int S1 = min(D, 20);
  int S2 = D - S1;
  assert(S1 <= 20);
  assert(S2 <= MAX);

  vector<int> rightMask(D);
  for (int i = S1; i < D; i++) {
    for (int j = S1; j < D; j++) {
      if (A[v[i]][v[j]]) {
        rightMask[i - S1] |= 1 << (j - S1);
      }
    }
  }

  vector<int> leftMask(D);
  for (int i = 0; i < D; i++) {
    for (int j = 0; j < S1; j++) {
      if (A[v[i]][v[j]]) {
        leftMask[i] |= 1 << j;
      }
    }
  }
  F0R(mask, 1 << S1) {
    if (mask == 0) {
      dp[mask] = 1;
    }
    else {
      int i = __builtin_ctz(mask);
      int nmask = mask ^ (1 << i);
      dp[mask] = dp[nmask] && ((leftMask[i] & nmask) == nmask);
    }
  }
  for (int i = 0; i < S1; i++) {
    F0R(mask, 1 << S1) {
      if (mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
    }
  }

  ll ans = 0;
  F0R(mask, 1 << S2) {
    if (mask == 0) {
      intersect[mask] = (1 << S1) - 1;
      can[mask] = 1;
    }
    else {
      int i = __builtin_ctz(mask);
      int nmask = mask ^ (1 << i);
      intersect[mask] = intersect[nmask] & leftMask[i + S1];
      can[mask] = can[mask ^ (1 << i)] && ((rightMask[i] & nmask) == nmask);
    }
    ans += can[mask] * dp[intersect[mask]];
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
    A[a][b] = A[b][a] = 1;
  }

  int ans = 0;
  REP(N) {
    pair<int, int> best = {1e9, -1};
    F0R(i, N) {
      if (!blocked[i]) {
        int d = 0;
        for (int j: adj[i]) {
          if (!blocked[j]) d++;
        }
        ckmin(best, {d, i});
      }
    }
    int i = best.second;
    assert(i != -1);
    ll c = solve(i);
    ans = (ans + c) % MOD;
    blocked[i] = true;
  }

  cout << ans << '\n';
}
