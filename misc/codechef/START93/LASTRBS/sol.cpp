#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

void solve() {
  int N; cin >> N;
  string S; cin >> S;
  vector<vector<vector<int>>> dp(N+2, vector<vector<int>>(N+2, vector<int>(2, -1)));

  auto f = y_combinator([&](auto f, int i, int bal, int p) -> int {
    if (bal < 0) return 0;
    if (i == N) return bal == 0;
    int& res = dp[i][bal][p];
    if (res != -1) return res;
    res = 0;
    if (i > 0 && S[i] == S[i-1]) {
      res = f(i+1, bal+(p?1:-1), p);
    }
    else {
      res |= f(i+1, bal+1, 1);
      res |= f(i+1, bal-1, 0);
    }
    // cout << i << ' ' << bal << ' ' << p << ": " << res << endl;
    return res;
  });

  string ans;
  auto recon = y_combinator([&](auto recon, int i, int bal, int p) -> void {
    if (i == N) return;
    if (i > 0 && S[i] == S[i-1]) {
      ans += p ? '(' : ')';
      recon(i+1, bal+(p?1:-1), p);
    }
    else {
      if (f(i+1, bal+1, 1)) {
        ans += '(';
        recon(i+1, bal+1, 1);
      }
      else {
        ans += ')';
        recon(i+1, bal-1, 0);
      }
    }
  });

  bool poss = f(0, 0, 0);
  if (poss) {
    cout << "YES\n";
    recon(0, 0, 0);
    cout << ans << '\n';
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
