#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

  template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

namespace ModInt { //{{{
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
        if (val > MOD) val -= MOD;
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
} //}}}
using mint = ModInt::mod_int<998244353>;

const int maxn = 1e5+5, cutoff = 320;

int ceil(int a, int b) {
  return (a + b - 1)/b;
}

int solve() {
  const int cutoff = 320;
  int n; cin >> n;
  vector<int> a(n);
  F0R(i, n) cin >> a[i];

  vector<vector<int>> dp1(n, vector<int>(cutoff, -1));
  vector<vector<int>> dp2(n, vector<int>(cutoff, -1));

  auto f = y_combinator([&](auto f, int i, int r) -> int {
    if (i == -1) return 0;
    int x = a[i];
    int d = ceil(x, r);

    int& res = r < cutoff ? dp1[i][r] : dp2[i][d];
    if (res != -1) return res;
    
    int nr = x / d;
    mint ans = mint(i + 1) * (d - 1) + (f(i-1, nr));
    //res = mult(i+1, d-1);
    //madd(res, f(i-1, nr));
    return res = ans;
  });


  mint total = 0;
  for (int i = 0; i < n; i++) {
    total += f(i, a[i]);
    //madd(total, f(i, a[i]));
  }
  return total;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
