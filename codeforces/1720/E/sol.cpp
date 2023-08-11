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

const int maxn = 505;
int N, K;
int A[maxn][maxn];
int cnt[maxn * maxn];
int xmin[maxn*maxn], xmax[maxn*maxn], ymin[maxn*maxn], ymax[maxn*maxn];
int XX[maxn*maxn], YY[maxn*maxn];
int X[maxn*maxn], Y[maxn*maxn];

bool in_bounds(int x, int y) {
  return 0 <= x && x < N && 0 <= y && y < N;
}

struct HorizBoard {
  vector<vector<int>> p, ret;

  HorizBoard() {
    p = vector<vector<int>>(N, vector<int>(N, 0));
  }

  void add(int x1, int y1, int x2, int y2) {
    ckmax(y1, 0);
    if (in_bounds(x1, y1)) {
      p[x1][y1]++;
      if (in_bounds(x2, y2+1)) p[x2][y2+1]--;
    }
  }

  void get_board() {
    ret = p;
    F0R(i, N) {
      FOR(j, 1, N) {
        ret[i][j] += ret[i][j-1];
      }
    }
  }
};

struct VertBoard {
  vector<vector<int>> p, ret;

  VertBoard() {
    p = vector<vector<int>>(N, vector<int>(N, 0));
  }

  void add(int x1, int y1, int x2, int y2) {
    ckmax(x1, 0);
    if (in_bounds(x1, y1)) {
      p[x1][y1]++;
      if (in_bounds(x2+1, y2)) p[x2+1][y2]--;
    }
  }

  void get_board() {
    ret = p;
    F0R(j, N) {
      FOR(i, 1, N) {
        ret[i][j] += ret[i-1][j];
      }
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  int D = 0;
  FOR(i, 1, N*N+1) {
    xmin[i] = ymin[i] = 1e9;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A[i][j];
      if (++cnt[A[i][j]] == 1) D++;

      ckmin(xmin[A[i][j]], i);
      ckmax(xmax[A[i][j]], i);
      ckmin(ymin[A[i][j]], j);
      ckmax(ymax[A[i][j]], j);
    }
  }

  FOR(i, 1, N*N+1) {
    int x = xmax[i] - xmin[i] + 1; 
    int y = ymax[i] - ymin[i] + 1;
    XX[i] = xmin[i], YY[i] = ymin[i];

    if (x > y) YY[i] -= x - y;
    else if (y > x) XX[i] -= y - x;
    X[i] = x, Y[i] = y;
  }

  if (D <= K) {
    cout << K - D << '\n';
  }
  else {
    HorizBoard horizBoard;
    VertBoard vertBoard;

    bool can_do_1 = false;
    int target = D - K; // target or target + 1
    for (int s = 1; s <= N; s++) {
      for (int i = 1; i <= N*N; i++) {
        if (cnt[i]) {
          int x = X[i], y = Y[i];
          int xx = XX[i], yy = YY[i];
          
          int d = s - max(x, y);
          if (d >= 0 && (xx-d >= 0 || yy-d >= 0)) {
            // add horiz
            horizBoard.add(xx-d, yy-d, xx-d, ymin[i]);
            // add vert
            vertBoard.add(xx-d+1, yy-d, xmin[i], yy-d);
          }
        }
      }

      horizBoard.get_board();
      vertBoard.get_board();

      const auto& A = horizBoard.ret;
      const auto& B = vertBoard.ret;

      F0R(i, N) F0R(j, N) {
        int sum = A[i][j] + B[i][j];
        if (in_bounds(i+s-1, j+s-1)) {
          if (sum == target || sum == target + 1) 
            can_do_1 = true;
        }
      }
    }

    cout << (can_do_1 ? 1 : 2) << '\n';
  }
}
