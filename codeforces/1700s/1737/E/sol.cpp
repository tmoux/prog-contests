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
using mint = ModInt::mod_int<1000000007>;

// For simplicity, we can assume the ant 1 is always going left, and ant n is always going right.
// If an ant survives, it can't be have started going right, since it would die to whoever was on its right.
// So it must be going left, and eaten everyone on its left going right.
// This looks like a "block" like this: >>>>>>>>><
//                                               |
//                                                you
// Any starting direction splits up the sequence into these blocks:
// >>>>>>< >>>>>< >>< < >><
// We can think of the process as the following steps:
// - Each block collapses into a single block, with weight the length of the block.
// - The blocks are "merged" from left to right, following the right-bias described in the problem statement.
//
// If ant i (1-indexed) survives, it must have eaten all the blocks to the left.
// This happens only when its block is size at least ceil(i/2), which happens with probability 2^(i/2).
// Next, it must eat all of the blocks to the right.
// To do so, the block directly to its right must have size at most i-1 (due to the right-bias).
// Let dp[i] be the probability of a size i block eating all the blocks to the right.
// Then dp[i] = sum_{j \in [i+1, 2*i-1]} 1/(2^(j-i)) * dp[j].
// The probability for ant i surviving is then 2^(i/2) * dp[i].
//
// Note that there in this formulation, some special care needs to be taken for i = n, since it doesn't really matter whether it is pointing left or right.
// In my original solution, I didn't take this into account, but my two formulas cancelled each other out and so I was just off by a factor of 2 for everything.
// I've included a more accurate solution here:

void solve() {
  int N; cin >> N;

  const mint half = mint(1) / 2;
  vector<mint> inv2(N+1);
  inv2[0] = 1;
  FOR(i, 1, N+1) inv2[i] = inv2[i-1] * half;

  vector<mint> dp(N+1); // probability of beating everyone to the right
  dp[N] = 1;
  mint cur = 0;
  for (int i = N-1, j = N; i >= 1; i--) {
    cur = (i+1 == N ? mint(1) : half) * (cur + dp[i+1]);
    while (j >= 2*i) {
      cur -= (j == N ? inv2[j-i-1] : inv2[j-i]) * dp[j];
      j--;
    }
    dp[i] = cur;
  }

  for (int i = 1; i <= N; i++) {
    mint prob = (i == N ? inv2[(i+1)/2-1] : inv2[(i+1)/2]) * dp[i];
    cout << prob << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
