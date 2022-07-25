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
  int K; cin >> K;

  int first = 0, second = 0;
  REP(K) {
    int N, M; cin >> N >> M;
    string S; cin >> S;
    string T; cin >> T;
    if (S[0] == 'D') {
      swap(S, T);
    }
    const int INF = 2e9;
    vector<int> A(N, INF);
    int cur = 0;
    int row = 0;
    for (char c: S) {
      if (c == 'R') cur++;
      else A[row++] = cur;
    }

    vector<int> B(M, INF);
    cur = 0;
    int col = 0;
    for (char c: T) {
      if (c == 'D') cur++;
      else B[col++] = cur;
    }

    auto go_p1_start = [&](int& row, int& col, int& dist) -> int {
      while (true) {
        ckmin(dist, B[col] - row - 1);
        bool blockedA = col+1 == A[row];
        if (blockedA) return 1;
        else if (!blockedA && row+1 == B[col+1]) return 0;
        else row++, col++;
      }
      assert(false);
    };

    auto go_p2_start = [&](int& row, int& col, int& dist) -> int {
      while (true) {
        ckmin(dist, A[row] - col - 1);
        bool blockedB = row+1 == B[col];
        if (blockedB) return 1;
        else if (!blockedB && col+1 == A[row+1]) return 0;
        else row++, col++;
      }
      assert(false);
    };

    int dist_to_bot_wall = INF;
    row = 0, col = 0;
    int winning_B = go_p1_start(row, col, dist_to_bot_wall);
    int exB = 0;
    while (dist_to_bot_wall > 0 && winning_B) {
      row++;
      dist_to_bot_wall--;
      winning_B = go_p1_start(row, col, dist_to_bot_wall);
      if (winning_B) {
        exB++;
      }
      else break;
    }
    second += exB;

    int dist_to_right_wall = INF;
    row = 0, col = 0;
    int winning_A = go_p2_start(row, col, dist_to_right_wall);
    int exA = 0;
    while (dist_to_right_wall > 0 && winning_A) {
      col++;
      dist_to_right_wall--;
      winning_A = go_p2_start(row, col, dist_to_right_wall);
      if (winning_A) {
        exA++;
      }
    }
    first += exA;
  }

  cout << (first > second ? "First" : "Second") << '\n';
}
