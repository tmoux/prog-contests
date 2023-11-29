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

// Either the answer is N, or there exists a minimum match x not taken
// Let's iterate over all possible x.
// This means we MUST take all y < x.
// In addition, we might as well take the biggest ones possible.
// Given a set of matches, we want to make the gap between them as big as possible
// So if we have a set of k numbers whose total length is s,
// we can cover a length of s + (k+1)*x - eps,
// so we need s + (k+1)*x > H and s <= H.
// We can precompute a knapsack DP to check all possible (s, k)

int solve() {
  int N, H; cin >> N >> H;
  vector<int> h(N);
  F0R(i, N) cin >> h[i];
  sort(all(h));

  using vi = vector<int>;
  using vvi = vector<vector<int>>;
  using vvvi = vector<vector<vector<int>>>;
  vvvi dp(2, vvi(N+1, vi(H+1, 0)));

  dp[0][0][0] = 1;

  int ans = N;
  for (int i = N-1; i >= 0; i--) {
    for (int k = 0; k <= N; k++) {
      for (int w = 0; w <= H; w++) {
        dp[1][k][w] = dp[0][k][w];
        dp[0][k][w] = 0;
      }
    }
    for (int k = 0; k <= N; k++) {
      for (int w = 0; w <= H; w++) {
        dp[0][k][w] = dp[1][k][w];
        if (k-1 >= 0 && w-h[i] >= 0)
          dp[0][k][w] |= dp[1][k-1][w-h[i]];
      }
    }

    int x = h[i];
    // min is exactly x
    int s = 0;
    int k = 0;
    for (int j = 0; j < i; j++) {
      k++;
      s += h[j];
    }

    for (int kk = 0; kk <= N; kk++) {
      for (int w = 0; w <= H; w++) {
        if (dp[1][kk][w] && s + w <= H && s + w + (k + kk + 1) * x > H && k + kk > 0) {
          ckmin(ans, k + kk);
        }
      }
    }

  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
