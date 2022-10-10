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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    int N = n;
    vector<vector<int>> A(n, vector<int>(n));
    F0R(i, n) {
      string s; cin >> s;
      F0R(j, n) {
        A[i][j] = s[j] - '0';
      }
    }

    vector<vector<bool>> mark(n, vector<bool>(n, false));
    int ans = 0;
    F0R(i, n) {
      F0R(j, n) {
        if (!mark[i][j]) {
          if (n % 2 == 1 && i == n/2 && j == n/2) continue;

          mark[i][j] = true;
          mark[j][N-i-1] = true;
          mark[N-j-1][i] = true;
          mark[N-i-1][N-j-1] = true;

          int c0 = 0, c1 = 0;
          (A[i][j] == 0 ? c0 : c1)++;
          (A[j][N-i-1] == 0 ? c0 : c1)++;
          (A[N-j-1][i] == 0 ? c0 : c1)++;
          (A[N-i-1][N-j-1] == 0 ? c0 : c1)++;

          ans += min(c0, c1);
        }
      }
    }

    cout << ans << '\n';

  }
}
