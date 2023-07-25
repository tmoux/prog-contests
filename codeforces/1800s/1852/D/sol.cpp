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
  string S; cin >> S;
  vector<int> d(N); F0R(i, N) d[i] = S[i] - 'A';
  using T = vector<array<int, 2>>;
  vector<array<T, 2>> dp(N);
  auto in_invls = [&](const T& v, int x) -> bool {
    for (auto [l, r]: v) {
      if (l <= x && x <= r) return true;
    }
    return false;
  };
  auto add = [](T a, int x) -> T {
    for (auto& [l, r]: a) {
      l += x, r += x;
    }
    return a;
  };
  auto merge = [&](T a, T b) -> T {
    T v;
    for (auto p: a) v.push_back(p);
    for (auto p: b) v.push_back(p);
    sort(all(v));
    T ret;
    for (auto [l, r]: v) {
      if (ret.empty() || ret.back()[1] + 1 < l) {
        ret.push_back({l, r});
      }
      else ckmax(ret.back()[1], r);
    }
    return ret;
  };

  F0R(i, 2) {
    dp[0][i] = {{d[0] != i, d[0] != i}};
  }
  for (int i = 1; i < N; i++) {
    dp[i][0] = merge(add(dp[i-1][0], (d[i] != d[i-1]) + (d[i] != 0)),
                     add(dp[i-1][1], (d[i] != d[i-1]) + 1 + (d[i] != 0)));
    dp[i][1] = merge(add(dp[i-1][0], (d[i] != d[i-1]) + 1 + (d[i] != 1)),
                     add(dp[i-1][1], (d[i] != d[i-1]) + (d[i] != 1)));
  }

  auto recon = y_combinator([&](auto recon, int i, int j, int x, string& ans) -> void {
    ans += 'A' + j;
    if (i > 0) {
      F0R(nj, 2) {
        int nx = x - (d[i] != d[i-1]) - (d[i] != j) - (j != nj);
        if (in_invls(dp[i-1][nj], nx)) {
          recon(i-1, nj, nx, ans);
          break;
        }
      }
    }
  });
  F0R(j, 2) {
    if (in_invls(dp[N-1][j], K)) {
      string ans;
      recon(N-1, j, K, ans);
      reverse(all(ans));
      cout << "YES" << '\n' << ans << '\n';
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
