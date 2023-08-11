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

const int MOD = 998244353;
void madd(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}

const int maxk = 17;
int dp[maxk+1][1<<maxk];

const int maxn = 1001;
int expo[maxn][maxk+1];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n;
  string s; cin >> s;
  int blanks = count(all(s), '?');

  for (int i = 1; i <= maxk; i++) {
    expo[0][i] = 1;
    for (int j = 1; j < maxn; j++) {
      expo[j][i] = mult(expo[j-1][i], i);
    }
  }

  auto add_to_dp = [&](int mask, int j) -> void {
    int x = __builtin_popcount(mask);
    for (int k = x; k <= maxk; k++) {
      madd(dp[k][mask], expo[j][k]);
    }
  };

  auto walk_substrings = [&](int L, int R, int exp, int b) -> void {
    int mask = 0;
    for (int j = 0; ; j++) {;
      int l = L-j;
      int r = R+j;
      if (l == r) continue;
      if (l < 0 || r >= n) break;
      if (s[l] == '?' && s[r] == '?') {
        exp++;
        b -= 2;
      }
      else if (s[l] == '?' && s[r] != '?') {
        b--;
        int c = s[r]-'a';
        mask |= (1<<c);
      }
      else if (s[l] != '?' && s[r] == '?') {
        b--;
        int c = s[l]-'a';
        mask |= (1<<c);
      }
      else if (s[l] != s[r]) break;

      add_to_dp(mask, exp+b);
    }

  };
  for (int i = 0; i < n; i++) { 
    int mask = 0;
    int exp = 0;
    int b = blanks;

    walk_substrings(i, i+1, exp, b);

    if (s[i] == '?') {
      exp++;
      b--;
    }
    add_to_dp(mask, exp+b);

    walk_substrings(i, i, exp, b);
  }

  for (int k = 0; k <= maxk; k++) {
    F0R(i, maxk) {
      F0R(mask, 1<<maxk) {
        if (mask & (1<<i)) {
          madd(dp[k][mask], dp[k][mask^(1<<i)]);
        }
      }
    }
  }

  int q; cin >> q;
  REP(q) {
    string t; cin >> t;
    int mask = 0;
    for (char c: t) mask |= (1<<(c-'a'));
    int ans = dp[sz(t)][mask];
    cout << ans << '\n';
  }
}
