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

const int maxn = 305;
int N, H;
int x[maxn];

int height(int l, int r) {
  return max(0, (x[r] - x[l] - 1) / 2);
}

ll dp[maxn][maxn];
ll f(int l, int r) {
  ll& res = dp[l][r];
  if (res != -1) return res;
  int curh = height(l, r);
  if (curh == 0) return res = 0;
  res = 1e18;
  for (int i = l; i < r; i++) {
    int hl = height(l, i);
    int hr = height(i+1, r);
    if (hl < curh && hr < curh) {
      ll t = (curh - hl) + f(l, i) + (curh - hr) + f(i+1, r);
      ckmin(res, t);
    }
  }
  return res;
}

ll ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(dp, -1, sizeof dp);
  cin >> N >> H;
  F0R(i, N) {
    cin >> x[i];
  }

  for (int i = N-1; i >= 0; i--) {
    ans[i] = 1e18;
    for (int j = i; j < N; j++) {
      int h = height(i, j);
      if (h <= H) {
        ckmin(ans[i], (H - h) + f(i, j) + ans[j+1]);
      }
    }
  }

  cout << ans[0] << '\n';

  for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
          cout << f(i, j) << ' ';
      }
      cout << '\n';
  }
}
