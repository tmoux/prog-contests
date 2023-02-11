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
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

const int maxn = 100;
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

ll brute(ll A, int B) {
  int N = 1;
  REP(A - 1) N *= 10;
  ll ans = 0;
  for (int x = N; x < N*10; x++) {
    vector<int> v;
    int y = x;
    while (y) {
      v.push_back(y % 10);
      y /= 10;
    }
    bool distinct = true;
    F0R(i, sz(v)-1) if (v[i] == v[i+1]) distinct = false;
    if (distinct && (x % 225) == B) {
      ans++;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ll A; cin >> A;
  int B; cin >> B;
  if (A <= 3) {
    cout << brute(A, B) << '\n';
  }
  else {
    auto cv = [](int i) -> pair<int, int> {
      int d = i % 10;
      int m = i / 10;
      return {m, d};
    };
    const int M = 90;
    Matrix T(M, M);
    F0R(i, M) {
      F0R(j, M) {
        auto [m1, d1] = cv(j);
        auto [m2, d2] = cv(i);
        if (d1 != d2 && (m1 + d2) % 9 == m2) {
          T.a[i][j] = 1;
        }
      }
    }

    mint ans = 0;
    T = T ^ (A - 4);

    Matrix I(M, 1);
    for (int x = 0; x < 100; x++) {
      int dig = x / 10;
      if (x % 10 == 0) {
        F0R(i, M) {
          auto [m, d] = cv(i);
          if (m == d % 9 && d != dig) I.a[i][0] = 1;
          else I.a[i][0] = 0;
        }
        I = T * I;
      }
      if (x % 10 == dig) continue;
      F0R(i, M) {
        auto [m, d] = cv(i);
        for (int l = 1; l <= 9; l++) {
          if (l == d) continue;
          if ((x + (4 * (m + l) * 25)) % 225 == B) {
            ans += I.a[i][0];
          }
        }
      }
    }
    cout << ans << '\n';
  }
}
