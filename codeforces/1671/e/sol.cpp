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
bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args&&... args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream& operator<<(ostream& os, const T_container& v) {
  os << '[';
  string sep;
  for (const T& x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int MOD = 998244353;

const int maxn = 1 << 18;
int S[maxn], n, dp[maxn];
vector<int> hashv[maxn];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  n = (1 << n) - 1;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    S[i] = c == 'A' ? 0 : 1;
  }
  for (int i = n; i >= 1; i--) {
    if (i * 2 > n) {
      hashv[i] = {S[i]};
    } else {
      int l = i * 2;
      int r = i * 2 + 1;
      if (hashv[l] > hashv[r]) swap(l, r);
      hashv[i] = {S[i]};
      hashv[i].insert(end(hashv[i]), all(hashv[l]));
      hashv[i].insert(end(hashv[i]), all(hashv[r]));
    }
  }
  for (int i = n; i >= 1; i--) {
    if (i * 2 > n)
      dp[i] = 1;
    else {
      int l = i * 2;
      int r = i * 2 + 1;
      bool equiv = hashv[l] == hashv[r];
      if (!equiv) {
        dp[i] = (2LL * dp[l] * dp[r]) % MOD;
      } else {
        dp[i] = (1LL * dp[l] * dp[r]) % MOD;
      }
    }
  }
  cout << dp[1] << '\n';
}

