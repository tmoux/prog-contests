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
vector<int> xs[maxn*maxn], ys[maxn*maxn];

bool in_bounds(int x, int y) {
  return 0 <= x && x < N && 0 <= y && y < N;
}

struct HorizBoard {
  vector<vector<int>> p, ret;
  vector<vector<array<int, 4>>> adds;

  HorizBoard() {
    p = vector<vector<int>>(N, vector<int>(N, 0));
    adds.resize(N + 1);
  }

  void add(int x1, int y1, int x2, int y2, int t) {
    ckmax(y1, 0);
    if (in_bounds(x1, y1)) {
      adds[t].push_back({x1, y1, x2, y2+1});
    }
  }

  void add_size(int s) {
    for (auto [x1, y1, x2, y2]: adds[s]) {
      p[x1][y1]++;
      if (in_bounds(x2, y2)) p[x2][y2]--;
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
  vector<vector<array<int, 4>>> adds;

  VertBoard() {
    p = vector<vector<int>>(N, vector<int>(N, 0));
    adds.resize(N + 1);
  }

  void add(int x1, int y1, int x2, int y2, int t) {
    ckmax(x1, 0);
    if (in_bounds(x1, y1)) {
      adds[t].push_back({x1, y1, x2+1, y2});
    }
  }

  void add_size(int s) {
    for (auto [x1, y1, x2, y2]: adds[s]) {
      p[x1][y1]++;
      if (in_bounds(x2, y2)) p[x2][y2]--;
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
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A[i][j];
      if (xs[A[i][j]].empty()) D++;
      xs[A[i][j]].push_back(i);
      ys[A[i][j]].push_back(j);
    }
  }

  if (D <= K) {
    cout << K - D << '\n';
  }
  else {
    HorizBoard horizBoard;
    VertBoard vertBoard;

    for (int i = 1; i <= N*N; i++) {
      if (!xs[i].empty()) {
        sort(all(xs[i]));
        sort(all(ys[i]));

        int minX = xs[i].front(), maxX = xs[i].back();
        int minY = ys[i].front(), maxY = ys[i].back();

        int x = maxX - minX + 1, y = maxY - minY + 1;
        // add diagonal
        int xx = minX, yy = minY;
        if (x > y) yy -= x - y;
        else if (y > x) xx -= y - x;
        
        for (int d = 0; xx-d >= 0 || yy-d >= 0; d++) {
          // add horiz
          horizBoard.add(xx-d, yy-d, xx-d, minY, max(x, y) + d);
          // add vert
          vertBoard.add(xx-d+1, yy-d, minX, yy-d, max(x, y) + d);
        }
      }
    }

    bool can_do_1 = false;
    int target = D - K; // target or target + 1
    for (int s = 1; s <= N; s++) {
      horizBoard.add_size(s);
      vertBoard.add_size(s);
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
