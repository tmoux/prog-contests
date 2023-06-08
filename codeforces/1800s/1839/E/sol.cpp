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

// If second player can win:
// If 1st takes MX, then take an odd element
// else if 1st takes an odd element, take MX
// else if 1st takes an even element, take another even element

// If first player can win: just always take the MX

const int maxn = 305;
int N;
int A[maxn];

int getMove() {
  int i; cin >> i;
  if (i == -1) exit(0);
  return i;
}

int dp[maxn][maxn*maxn+maxn];
int ty[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  FOR(i, 1, N+1) cin >> A[i];
  int S = accumulate(A+1, A+N+1, 0);
  dp[0][0] = 1;
  FOR(i, 1, N+1) {
    for (int s = 300*300; s >= 0; s--) {
      if (dp[i-1][s]) {
        dp[i][s] = 1;
        dp[i][s+A[i]] = 1;
      }
    }
  }

  if (S % 2 == 0 && dp[N][S/2]) {
    S /= 2;
    cout << "Second" << endl;
    for (int i = N; i >= 1; i--) {
      if (S >= A[i] && dp[i-1][S-A[i]]) {
        ty[i] = 1;
        S -= A[i];
      }
    }
    while (1) {
      // FOR(i, 1, N+1) {
      //   cout << A[i] << ' ';
      // }
      // cout << endl;
      int i = getMove();
      if (i == 0) return 0;
      int idx = -1;
      FOR(j, 1, N+1) {
        if (A[j] > 0 && ty[i] != ty[j]) {
          idx = j;
          break;
        }
      }
      assert(idx != -1);
      cout << idx << endl;
      int x = min(A[i], A[idx]);
      A[i] -= x;
      A[idx] -= x;
    }
  }
  else {
    cout << "First" << endl;
    while (1) {
      int idx = -1;
      FOR(j, 1, N+1) {
        if (A[j] > 0) {
          idx = j;
          break;
        }
      }
      assert(idx != -1);
      cout << idx << endl;

      int i = getMove();
      if (i == 0) return 0;
      int x = min(A[i], A[idx]);
      A[i] -= x;
      A[idx] -= x;
    }
  }
}
