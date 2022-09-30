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

const int maxn = 2005;

int N, M;
int A[maxn][maxn], B[maxn][maxn];

int a, b, c, d, x, y;
int cut;

int solve() {
  auto add_range = [&](int R1, int C1, int R2, int C2, int x) -> void {
    for (int i = R1; i <= R2; i++) {
      for (int j = C1; j <= C2; j++) {
        A[i][j] ^= x;
      }
    }
  };

  auto contains = [&](int R1, int C1, int R2, int C2, int x) -> pair<int, int> {
    for (int i = R1; i <= R2; i++) {
      for (int j = C1; j <= C2; j++) {
        if (A[i][j] == x) return {i, j};
      }
    }
    return {-1, -1};
  };

  auto sum_prefix = [&](int i, int j) -> int {
    int sum = 0;
    for (int k = 0; k < i; k++) {
      sum ^= A[k][j];
    }
    return sum;
  };

  auto row_sum = [&](int i) -> int {
    int sum = 0;
    for (int j = 0; j < M; j++) {
      sum ^= A[i][j];
    }
    return sum;
  };

  auto col_sum = [&](int j) -> int {
    int sum = 0;
    for (int i = 0; i < N; i++) {
      sum ^= A[i][j];
    }
    return sum;
  };

  auto even_sums = [&]() -> bool {
    F0R(i, N) if (row_sum(i) == 1) return false;
    F0R(j, M) if (col_sum(j) == 1) return false;
    return true;
  };

  for (int R1 = 0; R1 < N; R1++) {
    for (int C1 = 0; C1 < M; C1++) {
      vector<pair<int, int>> pos = {{-1, -1}, {-1, -1}};
      for (int R2 = R1; R2 < N; R2++) {
        for (int C2 = C1; C2 < M; C2++) {
          if (pos[A[R2][C2]] = {R2, C2};
          for (int add: {0, 1}) {
            auto [x1, y1] = pos[add];
            if (x1 != -1 && y1 != -1) {
              add_range(R1, C1, R2, C2, add);

              if (even_sums()) {
                for (int i = 1; i < N; i++) {
                  bool poss = true;
                  for (int j = 0; j < M; j++) {
                    if (sum_prefix(i, j) == 1) {
                      poss = false;
                      break;
                    }
                  }
                  if (poss) {
                    /*
                       cout << R1 << ' ' << C1 << ' ' << R2 << ' ' << C2 << endl;
                       cout << '\n';
                       F0R(i, N) {
                       F0R(j, M) {
                       cout << A[i][j] << ' ';
                       }
                       cout << '\n';
                       }
                       cout << '\n';
                       */
                    a = R1;
                    b = C1;
                    c = R2;
                    d = C2;
                    x = x1;
                    y = y1;
                    return i-1;
                  }
                }
              }
              add_range(R1, C1, R2, C2, add);
            }
          }
        }
      }
    }
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
      A[i][j] &= 1;
    }
  }

  cut = solve();
  if (cut != -1) {
    cout << a+1 << ' ' << b+1 << '\n';
    cout << c+1 << ' ' << d+1 << '\n';
    cout << x+1 << ' ' << y+1 << '\n';
    cout << 'R' << ' ' << cut+1 << '\n';
    return 0;
  }

  F0R(i, N) F0R(j, M) B[j][i] = A[i][j];
  swap(N, M);
  F0R(i, N) F0R(j, M) A[i][j] = B[i][j];

  cut = solve();
  if (cut != -1) {
    swap(a, b);
    swap(c, d);
    swap(x, y);

    cout << a+1 << ' ' << b+1 << '\n';
    cout << c+1 << ' ' << d+1 << '\n';
    cout << x+1 << ' ' << y+1 << '\n';
    cout << 'C' << ' ' << cut+1 << '\n';
    return 0;
  }

  cout << -1 << '\n';

  /*
     F0R(i, N) {
     int s = 0;
     F0R(j, M) {
     s += A[i][j];
     }
     cout << i << ": " << s << endl;
     }

     F0R(j, M) {
     int s = 0;
     F0R(i, N) {
     s += A[i][j];
     }
     cout << j << ": " << s << endl;
     }
     */
}
