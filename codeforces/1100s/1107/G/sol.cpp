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

const int maxn = 3e5+5;
int N, a;
ll P[maxn], Pr[maxn];
int D[maxn], Dr[maxn];

ll helper(ll *A, int* B, int l, int r) {
  int m = (l + r) / 2;
  ll ans = 0;
  int gap = 0;
  ll maxSum = -1e18, curSum = 0;
  ll rightSum = 0;
  for (int i = m+1, j = m+1; i <= r; i++) {
    rightSum += A[i];
    ckmax(gap, abs(B[i] - B[i-1]));
    while (j-1 >= l && abs(B[j] - B[j-1]) <= gap) {
      j--;
      curSum += A[j];
      ckmax(maxSum, curSum);
    }
    ckmax(ans, rightSum + maxSum - 1LL * gap * gap);
  }
  return ans;
}

ll f(int l, int r) {
  if (l > r) return 0;
  if (l == r) return P[l];
  int m = (l + r) / 2;


  ll ans = max(f(l, m), f(m+1, r));
  ckmax(ans, helper(P, D, l, r));
  ckmax(ans, helper(Pr, Dr, N-1-r, N-1-l));

  // cout << l << ' ' << m << ' ' << r << ": " << ans << endl;

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> a;
  F0R(i, N) {
    cin >> D[i];
    int x; cin >> x;
    P[i] = a - x;
  }
  F0R(i, N) {
    Pr[i] = P[N-1-i];
    Dr[i] = D[N-1-i];
  }

  cout << max(0LL, f(0, N-1)) << '\n';
}
