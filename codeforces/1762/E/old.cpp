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

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

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

      bool operator==(const mod_int& b) const {
        return val == b.val;
      }

      bool operator!=(const mod_int& b) const {
        return !(*this == b);
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

      mod_int& operator++(int) {
        return *this += 1;
      }

      mod_int& operator--(int) {
        return *this -= 1;
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
        i >> x.val; x.val %= MOD;
        return i;
      }
    };
} 
//}}}
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

namespace ModCombinatorics { // {{{
  vector<int> inv, _fac, _ifac;
  template<size_t N, int MOD>
    void init() {
      inv.resize(N);
      _fac.resize(N);
      _ifac.resize(N);
      inv[0] = inv[1] = 1;
      for (size_t i = 2; i < N; i++) {
        inv[i] = (MOD - (1LL * (MOD/i) * inv[MOD%i]) % MOD) % MOD;
      }
      _fac[0] = _ifac[0] = 1;
      for (size_t i = 1; i < N; i++) {
        _fac[i] = (1LL * i * _fac[i-1]) % MOD;
        _ifac[i] = (1LL * _ifac[i-1] * inv[i]) % MOD;
      }
    }

  mint choose(int n, int k) {
    if (n < k || k < 0) return 0;
    return mint(1) * _fac[n] * _ifac[k] * _ifac[n-k];
  }

  mint fac(int n) {
    return mint(_fac[n]);
  }

  mint ifac(int n) {
    return mint(_ifac[n]);
  }
}; 
// }}}
namespace MC = ModCombinatorics;

const int maxn = 5e5+5;

mint numtrees(int n) {
  if (n == 1) return 1;
  else return mint(n) ^ (n - 2);
}

int dp[maxn];

const int N = 10;

int f(int n) {
  if (dp[n] != -1) return dp[n];
  if (n == 1) return 0;
  mint ans = 0;
  mint odd = 0, even = 0;
  for (int s = 1; s <= n-1; s++) {
    mint mult = MC::choose(n - 2, s - 1);
    mult *= numtrees(n - s);

    // add direct edge
    mint add = (s&1 ? MOD - 1 : 1) * mint(s) * numtrees(s);
    add += mint(f(s)) * (s - 1);
    add *= mult;

    ans += add;

    /*
    if (n == N) {
      cout << s << ": ";
      if (add.val > 900000000) cout << -(MOD-add.val) << '\n';
      else cout << add << '\n';
    }
    */

    // (s&1?odd:even) += add;
  }

  return dp[n] = ans.val;
}

mint g(int n) {
  // 1-n
  mint sum1 = 0;
  for (int s = 1; s <= n-1; s++) {
    mint add = MC::choose(n-2, s-1);
    add *= numtrees(s);
    add *= numtrees(n - s);
    add *= s&1 ? MOD - 1 : 1;

    sum1 += add;
  }
  // 1-i, i-n
  mint sum2 = 0;
  for (int s = 2; s <= n-1; s++) {
    mint add = MC::choose(n-3, s-2);
    add *= numtrees(s);
    add *= numtrees(n - s);
    add *= s&1 ? MOD - 1 : 1;

    sum2 += add;
  }
  sum2 *= 2*(n-2);

  // i-j
  mint sum3 = 0;
  for (int s = 2; s <= n-1; s++) {
    mint add = MC::choose(n-4, s-2);
    add *= numtrees(s);
    add *= numtrees(n - s);
    add *= s&1 ? MOD - 1 : 1;
    add *= 2;

    sum3 += add;
  }
  sum3 *= mint(n-2) * (n-3) / 2;

  mint total = sum1 + sum2 + sum3;

  return total;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  MC::init<maxn, MOD>();
  memset(dp, -1, sizeof dp);

  int N; cin >> N;
  if (N&1) cout << 0 << '\n';
  else cout << g(N) << '\n';

  return 0;
}
