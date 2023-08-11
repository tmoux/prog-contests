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

mint choose(int n, int k) {
  if (n < k) return 0;
  mint num = 1;
  for (int i = 0; i < k; i++) num *= n-i;
  mint den = 1;
  for (int i = 0; i < k; i++) den *= k-i;
  return num / den;
}
vector<mint> brute(vector<int> A, int k) {
  int N = sz(A);
  vector<mint> ans(sz(A));
  F0R(i, N) {
    for (int j = 0; j <= i; j++) {
      ans[i] += choose(i+1-j, k) * A[j];
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, a1, x, y, m, K;
  cin >> N >> a1 >> x >> y >> m >> K;
  vector<int> A(N);
  A[0] = a1;
  FOR(i, 1, N) {
    A[i] = (1LL * A[i-1] * x + y) % m;
  }

  vector<mint> pfx(N);
  F0R(i, N) {
    pfx[i] = A[i];
    if (i > 0) pfx[i] += pfx[i-1];
  }
  vector<vector<mint>> ans(K+1, vector<mint>(N));
  for (int k = 1; k <= K; k++) {
    if (k == 1) {
      F0R(i, N) {
        mint add = mint(k) * (i-(k-1) < 0 ? mint(0) : pfx[i-(k-1)]);
        mint mult = 1;
        if (k > 1 && i-1 >= 0) {
          mult = ans[k-1][i-1];
          // DEBUG(ans[k-1][i-1]);
        }
        add *= mult;
        // DEBUG(add);

        ans[k][i] = add;
        if (i > 0) ans[k][i] += ans[k][i-1];
      }
    }
    else {
      F0R(i, N) {
        if (i < k-1) continue;
        mint add = mint(k);
        mint mult = 1;
        if (k > 1 && i-1 >= 0) {
          mult = ans[k-1][i-1];
          // DEBUG(ans[k-1][i-1]);
        }
        add *= mult;
        // DEBUG(add);

        ans[k][i] = add;
        if (i > 0) ans[k][i] += ans[k][i-1];
      }
    }
    if (k == K) {
      mint kfac = 1;
      for (int i = 1; i <= K; i++) kfac *= i;
      kfac = kfac.inverse();
      F0R(i, N) ans[K][i] *= kfac;
      // cout << "MINE" << ": " << ans[k] << endl;
    }

  }

  // DEBUG(A);
  // // cout << ans << endl;
  // auto b = brute(A, K);
  // // F0R(i, N) b[i] *= kfac.inverse();
  // cout << "BRUTE " << b << endl;

  ll res = 0;
  F0R(i, N) {
    res ^= 1LL * ans[K][i].val * (i+1);
  }
  cout << res << '\n';
}
