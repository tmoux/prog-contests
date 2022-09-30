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

struct Tracker { // {{{
  int len = -1;
  int excess = -2e9;
  int lo, hi;

  Tracker() {}
  Tracker(int _lo, int _hi, int x, int y) {
    lo = _lo;
    hi = _hi;
    len = 1;
    ckmax(excess, x - lo);
    ckmax(excess, y - hi);
  }

  void add_top_bot(int x, int y) {
    lo -= 2;
    len += 2;
    excess++;
    ckmax(excess, x - lo);
    ckmax(excess, y - hi);
  }

  int query(int l) {
    return l + len + max(0, excess - (l - lo));
  }
}; // }}}

int solve() {
  int M; cin >> M;
  vector<vector<int>> A(2, vector<int>(M));
  F0R(i, 2) {
    F0R(j, M) {
      cin >> A[i][j]; if (A[i][j] > 0) A[i][j]++;
    }
  }

  vector<vector<Tracker>> ts(2, vector<Tracker>(M));
  for (int k: {0, 1}) {
    ts[k][M-1] = Tracker(2*M-2, 2*M-1, A[k][M-1], A[k^1][M-1]);

    for (int j = M-2; j >= 0; j--) {
      ts[k][j] = ts[k][j+1];
      ts[k][j].add_top_bot(A[k][j], A[k^1][j]);
    }
  }

  int ans = 2e9;
  int cur_time = 0;
  F0R(j, M) {
    int k = j % 2;
    if (j > 0) cur_time = max(cur_time+1, A[k][j]);
    ckmin(ans, ts[k][j].query(cur_time));
    cur_time = max(cur_time+1, A[k^1][j]);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
