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

const int maxn = 2000;
ll N;
int K, MOD;

typedef unsigned long long ull;
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull reduce(ull a) { // a % b + (0 or b)
    return a - (ull)((__uint128_t(m) * a) >> 64) * b;
  }
};
FastMod red(1);

inline void madd(ull& a, ull b) {
  a = red.reduce(a + b);
}
inline ull msub(ull a, ull b) {
  madd(a, MOD - b);
  return a;
}
inline ull mult(ull a, ull b) {
  return red.reduce(a * b);
}
inline ull modexp(ull a, ull b) {
  ull r = 1;
  while (b) {
    if (b&1) r = mult(r, a);
    a = mult(a, a);
    b >>= 1;
  }
  return r;
}
inline ull inverse(ull x) {
  return modexp(x, MOD - 2);
}

struct Matrix
{
  ull m[maxn][maxn];
  int n;
  Matrix(int N_) {
    n = N_;
    memset(m, 0, sizeof m);
  }
};

Matrix operator*(Matrix a, Matrix b) {
  int n = a.n;
  Matrix res(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        madd(res.m[i][k], red.reduce(a.m[i][j]*b.m[j][k]));
      }
    }
  }
  return res;
}

Matrix power(Matrix a, ll p) {
  int n = a.n;
  Matrix ans(a.n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans.m[i][j] = (i==j);
    }
  }
  while (p) {
    if (p & 1) ans = ans * a;
    a = a * a;
    p >>= 1;
  }
  return ans;
}

int pmod(ll x) {
  return ((x % K) + K) % K;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K >> MOD;
  red = FastMod(MOD);
  Matrix A(K);
  ull aval = modexp(K, N-1);
  F0R(i, K) {
    F0R(j, K) {
      A.m[i][j] = aval;
    }
  }


  ull ans = 0;
  if (K % 2 == 1) {
    Matrix B(K);
    ull b1 = modexp(K-1, N);
    madd(b1, mult(K-1, modexp(MOD - 1, N)));
    b1 = mult(b1, inverse(K));
    ull b2 = b1;
    if (N % 2 == 0) {
      b2 = msub(b2, 1);
    }
    else {
      madd(b2, 1);
    }
    F0R(i, K) {
      F0R(j, K) {
        B.m[i][j] = i == j ? b1 : b2;
      }
    }

    F0R(s, K) {
      madd(ans, A.m[s][0]);
      int i = 0;
      while ((i * 2) % K != s) i++;
      madd(ans, MOD - B.m[pmod(s-(N%K)*i)][0]);
    }
  }
  else {
    Matrix B(K);
    ull b2 = msub(modexp(K - 2, N), modexp(MOD - 2, N));
    b2 = mult(b2, inverse(K));
    ull b1 = b2;
    if (N % 2 == 0) {
      madd(b1, modexp(2, N-1));
    }
    else {
      b1 = msub(b1, modexp(2, N-1));
    }

    F0R(i, K) {
      F0R(j, K) {
        if (i == j || i == (j + K/2) % K) B.m[i][j] = b1;
        else B.m[i][j] = b2;
      }
    }

    for (int s = 0; s < K; s += 2) {
      madd(ans, A.m[s][0]);
      madd(ans, MOD - B.m[pmod(s-s/2*(N%K))][0]);
    }
  }
  cout << ans % MOD << '\n';
}
