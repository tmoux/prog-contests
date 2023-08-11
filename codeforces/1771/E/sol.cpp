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

const int maxn = 405;
int N, M;

string grid[maxn];

vector<pair<int, char>> cols[maxn];

int up[maxn][maxn][2];
int down[maxn][maxn][2];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) cin >> grid[i];
  F0R(j, M) {
    F0R(i, N) {
      if (grid[i][j] != '.') {
        cols[j].push_back({i, grid[i][j]});
      }
    }
  }

  // populate up, down
  F0R(j, M) {
    auto it = cols[j].begin();
    F0R(i, N) {
      while (it != cols[j].end() && it->first <= i) {
        ++it;
      }
      if (it == cols[j].begin()) {
        up[i][j][0] = up[i][j][1] = i + 1;
      }
      else {
        auto [pi, c] = *prev(it);
        if (c == '#') {
          up[i][j][0] = up[i][j][1] = i - pi;
        }
        else {
          up[i][j][0] = i - pi;
          if (prev(it) == cols[j].begin()) {
            up[i][j][1] = i + 1;
          }
          else {
            auto [ppi, _] = *prev(prev(it));
            up[i][j][1] = i - ppi;
          }
        }
      }

      if (it == cols[j].end()) {
        down[i][j][0] = down[i][j][1] = N - i - 1;
      }
      else {
        auto [ni, c] = *it;
        if (c == '#') {
          down[i][j][0] = down[i][j][1] = ni - i - 1;
        }
        else {
          down[i][j][0] = ni - i - 1;
          if (next(it) == cols[j].end()) {
            down[i][j][1] = N - i - 1;
          }
          else {
            auto [nni, _] = *next(it);
            down[i][j][1] = nni - i - 1;
          }
        }
      }
    }
  }

  int ans = 0;

  F0R(i, N) FOR(j, 1, M-1) {
    int med = 0;
    for (int k = j; k < M-1; k++) {
      auto upd = [&](int a, int b, int c, int d) {
        if (a > 1 && c > 1 && b > 0 && d > 0) {
          ckmax(ans, (k - j + 1) + 2 * min(a, c) + 2 * min(b, d));
        }
      };

      int a = up  [i][j-1][0];
      int b = down[i][j-1][0];
      int c = up  [i][k+1][0];
      int d = down[i][k+1][0];

      int A = up  [i][j-1][1];
      int B = down[i][j-1][1];
      int C = up  [i][k+1][1];
      int D = down[i][k+1][1];

      if (grid[i][k] == '.' || (grid[i][k] == 'm' && med == 0)) {
        if (grid[i][k] == 'm') med++;

        if (med == 0) {
          upd(A, b, c, d);
          upd(a, B, c, d);
          upd(a, b, C, d);
          upd(a, b, c, D);
        }
        else {
          upd(a, b, c, d);
        }
      }
      else break;
    }
  }

  cout << ans << '\n';
}
