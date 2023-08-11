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

// If x people can be satisfied with k books, x people can be satisfied with k-1 books as well (we can just merge two groups together.)
// Thus it is equivalent to compute for each x, the maximum number of groups that can be formed such that x people are satisfied.
// Furthermore, if we are picking x people, we might as well pick the x least neediest people, since they are strictly easier to satisfy.
// The remaining (n - x) people can each form the own group, OR they can join another group to add to how many people are in the group (not everyone in a group has to be satisfied.)
// We want to make all x people satisfied, then the rest should form their own groups.

const int maxn = 3e5+5;
int N, Q, A[maxn];
int dp[maxn];

int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  FOR(i, 1, N+1) {
    cin >> A[i];
  }
  sort(A+1, A+N+1);
  FOR(i, 1, N+1) {
    if (i - A[i] >= 0) {
      dp[i] = dp[i - A[i]] + 1;
      ckmax(ans[dp[i] + N - i], i);
    }
    else {
      ckmax(ans[N - A[i] + 1], i);
    }
    ckmax(dp[i], dp[i-1]);
  }

  for (int i = N-1; i >= 2; i--) {
    ckmax(ans[i], ans[i+1]);
  }

  cin >> Q;
  F0R(i, Q) {
    int k; cin >> k;
    cout << ans[k] << '\n';
  }
}
