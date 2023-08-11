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

const int maxn = 105, maxr = 30000;
int N, R;

int dp[maxn][maxr];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> R;
  vector<pair<int, int>> pos, neg;
  F0R(i, N) {
    int a, b; cin >> a >> b;
    a = max(a, -b);
    (b >= 0 ? pos : neg).push_back({a, b});
  }

  int numpos = 0;
  sort(all(pos), greater());
  while (!pos.empty() && R >= pos.back().first) {
    numpos++;
    R += pos.back().second;
    pos.pop_back();
  }
  DEBUG(numpos);
  DEBUG(R);

  int ans = 0;
  sort(all(neg), [&](auto a, auto b) {
    return a.first + a.second > b.first + b.second;
  });
  dp[0][R] = 0;
  F0R(i, sz(neg)) {
    cout << neg[i] << endl;
    F0R(j, N+1) ckmax(dp[i][j], dp[i+1][j]);
    F0R(j, N+1) {
      // cout << i << ' ' << j << ": " << dp[i][j] << endl;
      if (dp[i][j] >= neg[i].first) {
        ckmax(dp[i+1][j+1], dp[i][j] + neg[i].second);
        ckmax(ans, numpos + j+1);
      }
    }
  }
  cout << ans << '\n';
}
