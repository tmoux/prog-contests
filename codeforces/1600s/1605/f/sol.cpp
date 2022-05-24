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

const int maxn = 85;

int N, K, MOD;

void madd(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}
void msub(int &a, int b) { madd(a, MOD - b); }
int mult(int a, int b) { return (1LL * a * b) % MOD; }
int modexp(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mult(res, a);
    a = mult(a, a);
    b >>= 1;
  }
  return res;
}

int comb[maxn][maxn];
int fac[maxn];
int pow2[maxn * maxn];

void precomp() {
  comb[0][0] = 1;
  for (int i = 1; i < maxn; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
    }
  }
  fac[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fac[i] = (1LL * i * fac[i - 1]) % MOD;
  }
  pow2[0] = 1;
  for (int i = 1; i < maxn * maxn; i++) {
    pow2[i] = (1LL * 2 * pow2[i - 1]) % MOD;
  }
}
int choose(int n, int k) {
  if (n < k)
    return 0;
  else
    return comb[n][k];
}
int perm(int n, int k) { 
  int res = 1;
  for (int i = 0; i < k; i++) {
    res = mult(res, n-i);
  }
  return res;
}

int dp[maxn][maxn];
int total_seqs[maxn][maxn];  // # of sequences of length i, using exactly j bits
int cnt_pos[maxn][maxn];     // # of sequences of distinct positive numbers of
                             // length i, using exactly j bits

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> K >> MOD;
  precomp();

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= K; j++) {
      total_seqs[i][j] = 
      total_seqs[i][j] = pow2[i * j];
      for (int k = 0; k < j; k++) {
        msub(total_seqs[i][j], mult(choose(j, k), total_seqs[i][k]));
      }
    }
  }


  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= K; j++) {
      int n = pow2[j];
      msub(n, 1);
      cnt_pos[i][j] = perm(n, i);

      for (int k = 0; k < j; k++) {
        msub(cnt_pos[i][j], mult(choose(j, k), cnt_pos[i][k]));
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= K; j++) {
      for (int a = 0; a < i; a++) {
        for (int b = 0; b < j; b++) {
          if (i == N && (N % 2) == 1 && a == i - 1) continue;
          int add = total_seqs[a][b];
          msub(add, dp[a][b]);
          add = mult(add, choose(i, a));
          add = mult(add, choose(j, b));
          add = mult(add, pow2[b * (i - a)]);
          add = mult(add, cnt_pos[i - a][j - b]);

          madd(dp[i][j], add);
        }
      }
    }
  }

  int ans = 0;
  for (int j = 0; j <= K; j++) {
    int add = total_seqs[N][j];
    msub(add, dp[N][j]);
    madd(ans, mult(choose(K, j), add));
  }
  cout << ans << '\n';
}
