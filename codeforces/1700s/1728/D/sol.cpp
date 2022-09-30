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

string solve() {
  string s; cin >> s;
  int N = sz(s);
  
  const int INV = -1e9;
  vector<vector<int>> dp(N, vector<int>(N, INV));

  auto f = y_combinator([&](auto f, int l, int r) -> int {
    if (l > r) return 0;
    if (dp[l][r] != INV) return dp[l][r];
    int& res = dp[l][r];

    auto eval = [](char a, char b, int x) -> int {
      if (x != 0) return x;
      else if (a < b) return 1;
      else if (a > b) return -1;
      else return 0;
    };
    // try take L
    res = min(eval(s[l], s[l+1], f(l+2, r)),
              eval(s[l], s[r], f(l+1, r-1)));
    // try take R
    ckmax(res, min(eval(s[r], s[r-1], f(l, r-2)),
                   eval(s[r], s[l], f(l+1, r-1))));
    return res;
  });

  int result = f(0, N-1);
  if (result == -1) {
    return "Bob";
  }
  else if (result == 0) {
    return "Draw";
  }
  else {
    return "Alice";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
