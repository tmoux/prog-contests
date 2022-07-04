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

  mint perm(int n, int k) {
    return choose(n, k) * fac(k);
  }
}; 
// }}}
namespace MC = ModCombinatorics;

const int maxn = 105;
int N;
array<int, 2> a[maxn];

int dist(int i, int j) {
  return abs(a[i][0] - a[j][0]) + abs(a[i][1] - a[j][1]);
}

vector<int> closest(int i) {
  vector<int> ret;
  int mn = 2e9;
  F0R(j, N) if (i != j) {
    int d = dist(i, j);
    if (d < mn) {
      mn = d;
      ret = {j};
    }
    else if (d == mn) {
      ret.push_back(j);
    }
  }
  return ret;
}

array<int, 3> quad[maxn];
array<int, 2> tri[maxn];
int bi[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  MC::init<maxn, MOD>();
  cin >> N;
  F0R(i, N) {
    cin >> a[i][0] >> a[i][1];
    quad[i] = {-1, -1, -1};
    tri[i] = {-1, -1};
    bi[i] = -1;
  }

  F0R(i, N) {
    auto v = closest(i);
    if (sz(v) >= 4) continue;
    else if (sz(v) == 3) {
      if (dist(v[0], v[1]) == dist(i, v[0]) &&
          dist(v[1], v[2]) == dist(i, v[0]) &&
          dist(v[0], v[2]) == dist(i, v[0])) {
        quad[i] = {v[0], v[1], v[2]};
      }
    }
    else if (sz(v) == 2) {
      if (dist(v[0], v[1]) == dist(i, v[0])) tri[i] = {v[0], v[1]};
    }
    else if (sz(v) == 1) {
      bi[i] = v[0];  
    }
    else assert(false);
  }
  int W = 0, X = 0, Y = 0;
  F0R(i, N) {
    if (quad[i][0] != -1) {
      int j = quad[i][0], k = quad[i][1], l = quad[i][2];
      set<int> A = {i, quad[i][0], quad[i][1], quad[i][2]};
      set<int> B = {j, quad[j][0], quad[j][1], quad[j][2]};
      set<int> C = {k, quad[k][0], quad[k][1], quad[k][2]};
      set<int> D = {l, quad[l][0], quad[l][1], quad[l][2]};

      if (A == B && B == C && C == D) {
        W++;
      }
    }
    if (tri[i][0] != -1) {
      int j = tri[i][0], k = tri[i][1];
      set<int> A = {i, tri[i][0], tri[i][1]};
      set<int> B = {j, tri[j][0], tri[j][1]};
      set<int> C = {k, tri[k][0], tri[k][1]};

      if (A == B && B == C) {
        X++;
      }
    }
    else if (bi[i] != -1 && bi[bi[i]] == i) {
      Y++;
    }
  }
  int Z = N - W - X - Y;
  W /= 4, X /= 3, Y /= 2;

  mint ans = 0;
  for (int w = 0; w <= W; w++) {
    for (int x = 0; x <= X; x++) {
      for (int y = 0; y <= Y; y++) {
        int cnt = w + x + y + (Z + 4*(W - w) + 3*(X - x) + 2*(Y - y));
        mint add = MC::perm(N, cnt);
        add *= MC::choose(W, w);
        add *= MC::choose(X, x);
        add *= MC::choose(Y, y);
        ans += add;
      }
    }
  }
  cout << ans << '\n';
}
