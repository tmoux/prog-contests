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

namespace ModInt {
  template<int MOD>
  struct mod_int {
    int val;

    operator int() const { return val; }
    mod_int() : val(0) {}
    mod_int(int _val) : val(_val % MOD) {}

    mod_int operator+() const {
      return mod_int(val);
    }
    mod_int operator-() const {
      return mod_int(MOD-val);
    }
    mod_int inverse() const {
      assert(val != 0);
      return *this ^ (MOD - 2);
    }

    mod_int& operator+=(const mod_int& b) {
      val += b.val;
      if (val >= MOD) val -= MOD;
      return *this;
    }
    mod_int& operator-=(const mod_int& b) {
      return *this += -b;
    }
    mod_int& operator*=(const mod_int& b) {
      val = (1LL*val*b.val) % MOD;
      return *this;
    }
    mod_int& operator/=(const mod_int& b) {
      val = (1LL*val*b.inverse().val) % MOD;
      return *this;
    }

    mod_int& operator+=(int b) {
      return *this += mod_int(b);
    }
    mod_int& operator-=(int b) {
      return *this -= mod_int(b);
    }
    mod_int& operator*=(int b) {
      return *this *= mod_int(b);
    }
    mod_int& operator/=(int b) {
      return *this /= mod_int(b);
    }

    friend mod_int operator+(const mod_int& a, const mod_int& b) {
      mod_int c = a; c += b;
      return c;
    }
    friend mod_int operator-(const mod_int& a, const mod_int& b) {
      mod_int c = a; c -= b;
      return c;
    }
    friend mod_int operator*(const mod_int& a, const mod_int& b) {
      mod_int c = a; c *= b;
      return c;
    }
    friend mod_int operator/(const mod_int& a, const mod_int& b) {
      mod_int c = a; c /= b;
      return c;
    }

    friend mod_int operator+(const mod_int& a, int b) {
      return a + mod_int(b);
    }
    friend mod_int operator-(const mod_int& a, int b) {
      return a - mod_int(b);
    }
    friend mod_int operator*(const mod_int& a, int b) {
      return a * mod_int(b);
    }
    friend mod_int operator/(const mod_int& a, int b) {
      return a / mod_int(b);
    }
    friend mod_int operator+(int a, const mod_int& b) {
      return mod_int(a) + b;
    }
    friend mod_int operator-(int a, const mod_int& b) {
      return mod_int(a) - b;
    }
    friend mod_int operator*(int a, const mod_int& b) {
      return mod_int(a) * b;
    }
    friend mod_int operator/(int a, const mod_int& b) {
      return mod_int(a) / b;
    }

    friend mod_int operator^(mod_int a, int b) {
      mod_int res(1);
      while (b > 0) {
        if (b&1) res *= a;
        a *= a;
        b >>= 1;
      }
      return res;
    }

    friend ostream& operator<<(ostream& o, const mod_int& x) {
      return o << x.val;
    };
    friend istream& operator>>(istream& i, mod_int& x) {
      return i >> x.val;
    }
  };
}
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

const int maxn = 70;
struct Matrix {
  int n, m;
  mint a[maxn][maxn];
  Matrix(int _n, int _m) {
    n = _n;
    m = _m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a[i][j] = 0;
      }
    }
  }

  Matrix operator*(Matrix r) {
    assert(m == r.n);
    Matrix res(n, r.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < r.m; j++) {
        for (int k = 0; k < m; k++) {
          res.a[i][j] += a[i][k] * r.a[k][j];
        }
      }
    }
    return res;
  }
};

Matrix operator^(Matrix r, ll b) {
  assert(r.n == r.m);
  Matrix res(r.n, r.m);
  for (int i = 0; i < r.n; i++) res.a[i][i] = 1;

  while (b) {
    if (b&1) res = res * r;
    r = r * r;
    b >>= 1;
  }
  return res;
}

ll N;
int M;
vector<string> vs;

bool check(string s) {
  for (auto t: vs) {
    if (s.find(t) != string::npos) return false;
  }
  return true;
}

int add0(int i) {
  const int ALL = (1 << 6) - 1;
  return (i << 1) & ALL;
}

int add1(int i) {
  const int ALL = (1 << 6) - 1;
  return ((i << 1) | 1) & ALL;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  vs.resize(M);
  F0R(i, M) cin >> vs[i];

  if (N <= 6) {
    // brute force
    mint res = 0;
    F0R(mask, 1 << N) {
      string s;
      F0R(i, N) {
        if (mask & (1 << i)) s += 'b';
        else s += 'a';
      }
      if (check(s)) res += 1;
    }
    cout << res << '\n';
  }
  else {
    Matrix A(64, 64);
    vector<int> ok(64);
    F0R(mask, 64) {
      string s;
      F0R(i, 6) {
        if (mask & (1 << i)) s += 'b';
        else s += 'a';
      }
      ok[mask] = check(s);
    }
    F0R(i, 64) {
      int j0 = add0(i);
      if (ok[i] && ok[j0]) {
        A.a[j0][i] += 1;
      }

      int j1 = add1(i);
      if (ok[i] && ok[j1]) {
        A.a[j1][i] += 1;
      }
    }

    Matrix E(64, 1);
    F0R(i, 64) if (ok[i]) E.a[i][0] = 1;

    Matrix ans = (A ^ (N - 6)) * E;
    mint res = 0;
    F0R(i, 64) res += ans.a[i][0];
    cout << res << '\n';
  }
}
