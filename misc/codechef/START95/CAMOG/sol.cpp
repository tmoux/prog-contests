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

const int maxn = 5e5+5;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

vector<int> getPrimes(int x) {
  vector<int> r;
  while (x > 1) {
    int p = spf[x];
    r.push_back(p);
    while (x % p == 0) x /= p;
  }
  return r;
}

map<vector<int>, int> CNT;

int N;

mint getProb(vector<int> v) {
  int mult = 1;
  for (auto x: v) mult *= x;
  int num = N / mult;

  int k = sz(v);

  int ans = 1;
  FOR(mask, 1, 1 << k) {
    int cnt = 0;
    int m = 1;
    F0R(i, k) {
      if (mask & (1 << i)) {
        cnt++;
        m *= v[i];
      }
    }
    ans += (cnt % 2 == 1 ? 1 : -1) * (num / m);
    cout << m << ' ' << cnt << ": " << ((cnt&1) ? 1 : -1) << ' ' << num / m << endl;
  }
  DEBUG(num);
  DEBUG(ans);
  return mint(ans) / num;
}

map<vector<int>, mint> memo;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N;
  // cout << getProb({2, 3}) << endl;
  // // cout << getProb({5}) << endl;
  // // cout << getProb({15}) << endl;
  // // cout << getProb({2, 3, 5}) << endl;
  // int cnt = 0;

  for (int x = 1; x <= N; x++) {
    auto primes = getPrimes(x);
    int k = sz(primes);
    F0R(mask, 1 << k) {
      vector<int> v;
      F0R(i, k) {
        if (mask & (1 << i)) v.push_back(primes[i]);
      }
      CNT[v]++;
    }
  }
  vector<mint> ans;
  for (int x = 1; x <= N; x++) {
    auto primes = getPrimes(x);
    if (memo.count(primes)) {
      ans.push_back(memo[primes]);
    }
    else {
      int K = sz(primes);
      vector<mint> dp(1 << K);
      vector<mint> probs(1 << K);
      F0R(mask, 1 << K) {
        vector<int> v;
        F0R(i, K) if (mask & (1 << i)) v.push_back(primes[i]);
        probs[mask] = mint(CNT[v]) / N;
      }
      for (int sz = 1; sz <= K; sz++) {
        F0R(mask, 1 << K) {
          mint p = probs[mask];
          if (__builtin_popcount(mask) == sz) {
            FOR(m2, 0, (1 << K)-1) {
              if ((m2 & mask) == m2) {
                mint p_m = probs[m2];
                mint probEnd = p_m / (1 - p);
                mint a = p / (p + p_m);
                mint expect = mint(1) / (1 - a);
                if (x == 2) {
                  cout << mask << ' ' << m2 << ": " << p << ' ' << p_m << endl;
                }

                dp[mask] += probEnd * (expect + dp[mask]);
              }
            }
          }
        }
      }
      memo[primes] = dp[(1 << K) - 1];
      ans.push_back(memo[primes]);
    }
  }
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}
