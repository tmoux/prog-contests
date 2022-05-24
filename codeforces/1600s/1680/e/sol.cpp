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
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    int n;
    cin >> n;
    vector<vector<int>> g(2, vector<int>(n, 0));
    F0R(i, 2) {
      string s;
      cin >> s;
      F0R(j, n) g[i][j] = s[j] == '*' ? 1 : 0;
    }
    vector<bool> hasl(n), hasr(n);
    F0R(i, n) {
      hasl[i] = g[0][i] | g[1][i];
      if (i > 0 && hasl[i - 1])
        hasl[i] = 1;
    }
    F0Rd(i, n) {
      hasr[i] = g[0][i] | g[1][i];
      if (i < n - 1 && hasr[i + 1])
        hasr[i] = 1;
    }
    vector<vector<int>> dpl(2, vector<int>(n));
    vector<vector<int>> dpr(2, vector<int>(n));

    F0R(j, n) {
      F0R(i, 2) {
        if (j > 0 && hasl[j - 1])
          dpl[i][j] =
              min(dpl[i][j - 1] + 1 + g[i ^ 1][j], dpl[i ^ 1][j - 1] + 2);
        else dpl[i][j] = g[i ^ 1][j];
      }
    }

    F0Rd(j, n) {
      F0R(i, 2) {
        if (j < n - 1 && hasr[i + 1])
          dpr[i][j] =
              min(dpr[i][j + 1] + 1 + g[i ^ 1][j], dpr[i ^ 1][j + 1] + 2);

        else dpr[i][j] = g[i ^ 1][j];
      }
    }

    int ans = 2e9;
    F0R(j, n) {
      F0R(i, 2) {
        bool a = j > 0 && hasl[j - 1];
        bool b = j < n - 1 && hasr[j + 1];

        int l1 = a ? dpl[i][j - 1] + 1 : 0;
        int l2 = a ? dpl[i ^ 1][j - 1] + 2 : 0;

        int r1 = b ? dpr[i][j + 1] + 1 : 0;
        int r2 = b ? dpr[i ^ 1][j + 1] + 2 : 0;

        ckmin(ans, l1 + r1 + g[i ^ 1][j]);
        if (a) ckmin(ans, l2 + r1);
        if (b) ckmin(ans, l1 + r2);
        if (a && b) ckmin(ans, l2 + r2);
      }
    }
    cout << ans << '\n';
  }
}

