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
bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args&&... args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream& operator<<(ostream& os, const T_container& v) {
  os << '[';
  string sep;
  for (const T& x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

namespace ModInt {  //{{{
template <int MOD>
struct mod_int {
  int val;

  mod_int() : val(0) {}
  mod_int(int _val) : val(_val % MOD) {}

  mod_int operator+() const { return mod_int(val); }
  mod_int operator-() const { return mod_int(MOD - val); }
  mod_int inverse() const {
    assert(val != 0);
    return *this ^ (MOD - 2);
  }

  bool operator==(const mod_int& b) const { return val == b.val; }

  bool operator!=(const mod_int& b) const { return !(*this == b); }

  mod_int& operator+=(const mod_int& b) {
    val += b.val;
    if (val >= MOD)
      val -= MOD;
    return *this;
  }
  mod_int& operator-=(const mod_int& b) { return *this += -b; }
  mod_int& operator*=(const mod_int& b) {
    val = (1LL * val * b.val) % MOD;
    return *this;
  }
  mod_int& operator/=(const mod_int& b) {
    val = (1LL * val * b.inverse().val) % MOD;
    return *this;
  }

  mod_int& operator++(int) { return *this += 1; }

  mod_int& operator--(int) { return *this -= 1; }

  friend mod_int operator+(const mod_int& a, const mod_int& b) {
    mod_int c = a;
    c += b;
    return c;
  }
  friend mod_int operator-(const mod_int& a, const mod_int& b) {
    mod_int c = a;
    c -= b;
    return c;
  }
  friend mod_int operator*(const mod_int& a, const mod_int& b) {
    mod_int c = a;
    c *= b;
    return c;
  }
  friend mod_int operator/(const mod_int& a, const mod_int& b) {
    mod_int c = a;
    c /= b;
    return c;
  }

  friend mod_int operator^(mod_int a, int b) {
    mod_int res(1);
    while (b > 0) {
      if (b & 1)
        res *= a;
      a *= a;
      b >>= 1;
    }
    return res;
  }

  friend ostream& operator<<(ostream& o, const mod_int& x) {
    return o << x.val;
  };
  friend istream& operator>>(istream& i, mod_int& x) {
    i >> x.val;
    x.val %= MOD;
    return i;
  }
};
}  // namespace ModInt
//}}}

void madd(int& a, int b, int MOD) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}
int mult(int a, int b, int MOD) { return (1LL * a * b) % MOD; }
int modexp(int a, int b, int MOD) {
  int res = 1;
  while (b > 0) {
    if (b & 1)
      res = mult(res, a, MOD);
    a = mult(a, a, MOD);
    b >>= 1;
  }
  return res;
}
int inverse(int x, int MOD) { return modexp(x, MOD - 2, MOD); }

int A, B, P;

int f(int x, int y) {
  int v = A * B + x * y;
  if (v % P == 0) {
    return 1;
  } else {
    int u = A * x + B * y;
    // cout << u << ' ' << v << endl;
    return mult(u, inverse(v, P), P);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> A >> B >> P;
  int K; cin >> K;

  /*
  F0R(x, P) {
    cout << x << ": " << inverse(x, P) << endl;
  }
  */

  F0R(x, P) {
    F0R(y, P) {
      cout << f(x, y) << ' ';
    }
    cout << '\n';
  }

  int x = f(K, K-1);
  DEBUG(x);
  for (int k = K-2; k >= 1; k--) {
    x = f(x, k);
    cout << k << ": " << x << endl;
  }
  cout << x << '\n';
}
