#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
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
    mod_int(ll _val) : val((_val + MOD) % MOD) {}

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

mint probIntersect(int L1, int R1, int L2, int R2) {
  if (L1 > R1 || L2 > R2) return mint(0);
  int s1 = R1 - L1 + 1;
  int s2 = R2 - L2 + 1;
  int l = max(L1, L2);
  int r = min(R1, R2);
  int inter = max(0, r - l + 1);
  return (mint(inter) / (mint(s1) * mint(s2)));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> L(N); for (auto& x: L) cin >> x;
  vector<int> R(N); for (auto& x: R) cin >> x;
  vector<int> S(N);
  F0R(i, N) {
    S[i] = R[i] - L[i] + 1;
  }

  if (N == 1) {
    cout << 1 << '\n';
    return 0;
  }

  vector<mint> D(N), F(N);
  D[0] = 1;
  F[0] = mint(1) - probIntersect(L[0], R[0], L[1], R[1]);
  FOR(i, 1, N) {
    mint p = probIntersect(L[i-1], R[i-1], L[i], R[i]);
    int l = max(L[i-1], L[i]);
    int r = min(R[i-1], R[i]);
    D[i] = mint(1) - p;

    if (i + 1 < N) {
      if (l <= r) {
        int len = r - l + 1;
        // case 1: in [l, r]
        {
          mint p1 = mint(S[i-1] - 1) / mint(S[i-1]);
          mint p2 = mint(len) / mint(S[i]);
          mint p3 = mint(1) - probIntersect(l, r, L[i+1], R[i+1]);
          F[i] += p1 * p2 * p3;
        }
        // case 2: (r, ]
        {
          mint p1 = 1;
          mint p2 = (R[i] - r) / mint(S[i]);
          mint p3 = mint(1) - probIntersect(r+1, R[i], L[i+1], R[i+1]);
          F[i] += p1 * p2 * p3;
        }
        // case 3: [ , l)
        {
          mint p1 = 1;
          mint p2 = (l - L[i]) / mint(S[i]);
          mint p3 = mint(1) - probIntersect(L[i], l-1, L[i+1], R[i+1]);
          F[i] += p1 * p2 * p3;
        }
      }
      else {
        F[i] = mint(1) - probIntersect(L[i], R[i], L[i+1], R[i+1]);
      }
    }
  }

  mint ans = 0;
  mint sum = 0;
  F0R(i, N) {
    ans += D[i];
    sum += D[i];
  }
  F0R(i, N) {
    mint cursum = sum;
    if (i-1 >= 0) cursum -= D[i-1];
    cursum -= D[i];
    if (i+1 < N) cursum -= D[i+1];
    ans += D[i] * cursum;
  }

  FOR(i, 0, N-1) {
    ans += mint(2) * F[i];
  }

  cout << ans << '\n';
}
