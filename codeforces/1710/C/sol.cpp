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

// The given constraint is difficult to work with, so let's try to change it to make it more manageable.
// Since a + b = (a ^ b) + 2 * (a & b), we have
// (a ^ b) + (b ^ c) > (a ^ c) <=>
// (a + b - 2(a&b)) + (b + c - 2(b&c)) > a + c - 2(a&c) <=>
// b > a&b + b&c - a&c.
// We can show that the RHS is always AT MOST b, and the only way for equality to hold is for each bit i, at least one of a_i or c_i to be equal to b_i.
// (In other words, we can't have a triple of bits (1, 0, 0) or (0, 1, 1)).
// We can then count the number of 'bad' triples using inclusion-exclusion, and then take the complement to find the answer.

// refactor recursive expressions to not have two recursive functions
// Compute bottom-up dp to save memory

const int maxn = 2e5+5;
int dp[maxn][2][2][2], dp2[maxn][2][2][2];
int N, D[maxn];

mint count_1_bad(int i, int x, int y, int z) {
  if (i == N) return 1;
  int& res = dp[i][x][y][z];
  if (res != -1) return res;
  auto trans = [&](int a, int b, int c) -> array<int, 4> {
    if ((x || a <= D[i]) && (y || b <= D[i]) && (z || c <= D[i])) {
      return {1, x | (a < D[i]), y | (b < D[i]), z | (c < D[i])};
    }
    else return {0, 0, 0, 0};
  };
  vector<array<int, 3>> vs = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1},
  };
  mint ans = 0;
  for (auto [a, b, c]: vs) {
    auto [p, nx, ny, nz] = trans(a, b, c);
    if (p) ans += count_1_bad(i+1, nx, ny, nz);
  }
  return res = ans.val;
}

mint count_2_bad(int i, int x, int y, int z) {
  if (i == N) return 1;
  int& res = dp2[i][x][y][z];
  if (res != -1) return res;
  auto trans = [&](int a, int b, int c) -> array<int, 4> {
    if ((x || a <= D[i]) && (y || b <= D[i]) && (z || c <= D[i])) {
      return {1, x | (a < D[i]), y | (b < D[i]), z | (c < D[i])};
    }
    else return {0, 0, 0, 0};
  };
  vector<array<int, 3>> vs = {
    {0, 0, 0},
    {0, 0, 1},
    {1, 1, 0},
    {1, 1, 1},
  };
  mint ans = 0;
  for (auto [a, b, c]: vs) {
    auto [p, nx, ny, nz] = trans(a, b, c);
    if (p) ans += count_2_bad(i+1, nx, ny, nz);
  }
  return res = ans.val;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  N = sz(s);
  F0R(i, N) D[i] = s[i] - '0';
  mint X = 0;
  F0R(i, N) {
    X = X * 2 + D[i];
  }
  memset(dp, -1, sizeof dp);
  memset(dp2, -1, sizeof dp2);
  mint my_c1 = count_1_bad(0, 0, 0, 0);
  mint my_c2 = count_2_bad(0, 0, 0, 0);
  mint my_c3 = X + 1;
  mint total_bad = 3 * my_c1 - 3 * my_c2 + my_c3;
  mint total_good = ((X + 1) ^ 3) - total_bad;

  cout << total_good << '\n';
}
