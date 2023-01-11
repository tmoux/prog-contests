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

int MOD;
void madd(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}
int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}
const int maxn = 650;
int part[maxn][maxn];
int partitions[3][maxn];

void self_convolve(int *a, int *b) {
  F0R(i, maxn) F0R(j, maxn) {
    if (i + j < maxn) {
      madd(b[i+j], mult(a[i], a[j]));
    }
  }
}

// l       v     r
// T T T T F F F F
template <class Integer, class F>
Integer find_first_false(Integer l, Integer r, F &&f) {
  return *ranges::partition_point(ranges::views::iota(l, r), f);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T, u; cin >> T >> u;
  if (u == 2) {
    cin >> MOD;
    partitions[0][0] = part[0][0] = 1;
    for (int n = 1; n < maxn; n++) {
      for (int k = 1; k <= n; k++) {
        if (n-k >= 0) madd(part[n][k], part[n-k][k]);
        if (n-1 >= 0 && k-1 >= 0) madd(part[n][k], part[n-1][k-1]);
        madd(partitions[0][n], part[n][k]);
      }
    }
    for (int i = 1; i <= 2; i++) {
      self_convolve(partitions[i-1], partitions[i]);
    }
  }

  auto solve1 = [&](int n) {
    int X = find_first_false(1, n+1, [n](int x) {return (n + x - 1) / x >= x;}) - 1;
    int Y = (n + X - 1) / X;
    cout << X << ' ' << Y << '\n';
    F0R(i, X) {
      F0R(j, Y) {
        cout << (n-- > 0 ? '#' : '.');
      }
      cout << '\n';
    }
  };
  auto solve2 = [&](int n) {
    int X = find_first_false(1, n+1, [n](int x) {return (n + x - 1) / x >= x;}) - 1;
    int Y = (n + X - 1) / X;
    int ans = 0;
    int perim = 2 * (X + Y);
    while (n <= X * Y && X * Y - n < X) {
      int g = X * Y - n;
      madd(ans, partitions[2][g]);
      if (X != Y) madd(ans, partitions[2][g]);
      X--, Y++;
    }
    cout << perim << ' ' << ans << '\n';
  };
  while (T--) {
    int N; cin >> N;
    u == 1 ? solve1(N) : solve2(N);
  }
}
