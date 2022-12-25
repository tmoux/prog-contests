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

int N, MOD;
void madd(int& a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}
int mult(int a, int b) {
    return (1LL*a*b) % MOD;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,MOD-2);
}

const int maxn = 5005;
int choose[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  cin >> MOD;

  vector<int> pow2(N + 5);
  pow2[0] = 1;
  for (int i = 1; i < N + 5; i++) {
    pow2[i] = mult(2, pow2[i-1]);
  }
  vector<int> fac(N+5);
  fac[0] = 1;
  for (int i = 1; i < N + 5; i++) {
    fac[i] = mult(i, fac[i-1]);
  }
  for (int i = 0; i <= N; i++) {
    choose[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      choose[i][j] = choose[i-1][j-1];
      madd(choose[i][j], choose[i-1][j]);
    }
  }

  int W = N / 2;
  vector<int> ways(N + 5);
  for (int w1 = 0; w1 < N; w1++) {
    for (int w2 = 0; w2 < N; w2++) {
      if (w1 < W && w2 < W && w1 + 1 + w2 >= W && w1 + 1 + w2 < N) {
        ways[w1 + w2]++;
      }
    }
  }

  int ans = 0;
  for (int w = 0; w < N; w++) {
    if (w + 1 >= W && w + 1 < N) {
      int s = N - w - 1;
      int ws = ways[w];
      assert(s > 0);
      if (s <= 2) {
        madd(ans, mult(ws, fac[w]));
      }
      else {
        int extra = s - 2;
        int add = 0;
        for (int i = 0; i <= extra; i++) {
          madd(add, mult(choose[extra][i], mult(fac[i], choose[w+i][i])));
        }
        add = mult(add, fac[w]);
        add = mult(add, ws);
        madd(ans, add);
      }
    }
  }
  ans = mult(ans, N);
  cout << ans << '\n';
}
