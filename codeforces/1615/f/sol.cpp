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

mint solve() {
  int N; cin >> N;
  string s, t; cin >> s >> t;
  for (int i = 0; i < N; i += 2) {
    if (s[i] == '0') s[i] = '1';
    else if (s[i] == '1') s[i] = '0';
    if (t[i] == '0') t[i] = '1';
    else if (t[i] == '1') t[i] = '0';
  }
  string sR = s; reverse(all(sR));
  string tR = t; reverse(all(tR));
  s = '#' + s;
  t = '#' + t;
  sR = '#' + sR;
  tR = '#' + tR;

  auto computeDP = [&](string s, string t) -> vector<vector<mint>> {
    int first_s = N+1;
    for (int i = N; i >= 1; i--) if (s[i] == '1') first_s = i;
    int first_t = N+1;
    for (int i = N; i >= 1; i--) if (t[i] == '1') first_t = i;
    vector<vector<mint>> dp(N+1, vector<mint>(N+1));
    for (int i = 0; i < first_s; i++) {
      for (int j = 0; j < first_t; j++) {
        dp[i][j] = 1;
      }
    }
    vector<vector<mint>> pfx(N+1, vector<mint>(N+1)); // pfx[i][j] = sum_k {0..j-1} dp[i][j]
    int pj = 1;
    for (int j = 1; j <= N; j++) {
      mint sum = 0;
      if (t[j] == '1') {
        pj = j;
      }
      for (int i = 0; i <= N; i++) {
        if (t[j] != '0') pfx[i][j] = pfx[i][j-1] + dp[i][j-1];
        else pfx[i][j] = pfx[i][j-1];
      }
      for (int i = 1; i <= N; i++) {
        if (s[i] == '1') sum = 0;
        if (s[i] != '0') {
          sum += pfx[i-1][j] - pfx[i-1][pj-1];
        }
        dp[i][j] = sum;
        if (i < first_s && j < first_t) dp[i][j] += 1;
      }
    }
    return dp;
  };

  auto dpL = computeDP(s, t);
  auto dpRR = computeDP(sR, tR);
  vector<vector<mint>> dpR(N+2, vector<mint>(N+2));
  F0R(i, N+1) F0R(j, N+1) dpR[N+1-i][N+1-j] = dpRR[i][j];

  mint ans = 0;
  FOR(i, 1, N+1) {
    FOR(j, 1, N+1) {
      if (s[i] != '0' && t[j] != '0')
        ans += abs(i - j) * dpL[i-1][j-1] * dpR[i+1][j+1];
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
