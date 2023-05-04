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
int N, M;

string S[maxn][maxn], T[maxn][maxn];

vector<array<int, 4>> ans;

void move(int i1, int j1, int i2, int j2) {
  assert(i1 == i2 || j1 == j2);
  ans.push_back({i1, j1, i2, j2});
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) {
    F0R(j, M) {
      cin >> S[i][j];
      reverse(all(S[i][j]));
    }
  }
  F0R(i, N) {
    F0R(j, M) {
      cin >> T[i][j];
      reverse(all(T[i][j]));
    }
  }

  // clear (0, M-1)
  for (char c: S[0][M-1]) {
    if (c == '0') {
      move(0, M-1, 0, 0);
    }
    else {
      move(0, M-1, N-1, M-1);
    }
  }
  // clear top row
  for (int j = 0; j < M-1; j++) {
    for (char c: S[0][j]) {
      move(0, j, 0, M-1);
      if (c == '0') {
        move(0, M-1, 0, 0);
      }
      else {
        move(0, M-1, N-1, M-1);
      }
    }
  }
  // clear right col
  for (int i = 1; i < N; i++) {
    for (char c: S[i][M-1]) {
      move(i, M-1, 0, M-1);
      if (c == '0') {
        move(0, M-1, 0, 0);
      }
      else {
        move(0, M-1, N-1, M-1);
      }
    }
  }
  // clear rest
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < M-1; j++) {
      for (char c: S[i][j]) {
        if (c == '0') {
          move(i, j, 0, j);
          if (j != 0) {
            move(0, j, 0, 0);
          }
        }
        else {
          move(i, j, i, M-1);
          if (i != N-1) {
            move(i, M-1, N-1, M-1);
          }
        }
      }
    }
  }

  // fill rest
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < M-1; j++) {
      for (char c: T[i][j]) {
        if (c == '0') {
          if (j != 0) {
            move(0, 0, 0, j);
          }
          move(0, j, i, j);
        }
        else {
          if (i != N-1) {
            move(N-1, M-1, i, M-1);
          }
          move(i, M-1, i, j);
        }
      }
    }
  }

  // fill top row
  for (int j = 0; j < M-1; j++) {
    for (char c: T[0][j]) {
      if (c == '0') {
        move(0, 0, 0, M-1);
      }
      else {
        move(N-1, M-1, 0, M-1);
      }
      move(0, M-1, 0, j);
    }
  }

  // fill right col
  for (int i = 1; i < N; i++) {
    for (char c: T[i][M-1]) {
      if (c == '0') {
        move(0, 0, 0, M-1);
      }
      else {
        move(N-1, M-1, 0, M-1);
      }
      move(0, M-1, i, M-1);
    }
  }

  // fill (0, M-1)
  for (char c: T[0][M-1]) {
    if (c == '0') {
      move(0, 0, 0, M-1);
    }
    else {
      move(N-1, M-1, 0, M-1);
    }
  }

  cout << sz(ans) << '\n';
  for (auto [a, b, c, d]: ans) {
    cout << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << '\n';
  }
}
