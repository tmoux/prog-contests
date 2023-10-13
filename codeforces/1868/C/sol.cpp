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

mint modpow(mint a, ll b)
{
  mint res(1);
  while (b > 0)
  {
    if (b & 1)
      res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}

const int maxl = 200, maxm = 1e5+5;
mint f[maxl][maxm];

void precompute(ll N, int M) {
  for (int l = 1; l < maxl; l++) {
    mint sum = 0;
    mint mult = modpow(M, N - l);
    for (int m = 1; m <= M; m++) {
      mint ml = modpow(m, l);
      f[l][m] = (-sum + mint(m) * ml) * mult;
      sum += ml;
    }
  }
}

map<pair<ll, int>, pair<mint, vector<mint>>> memo;
pair<mint, vector<mint>> solvePerfect(ll N, int M) {
  if (N == 0) return {0, {}};
  if (memo.count({N, M})) return memo[{N, M}];

  vector<mint> v = {1};
  mint ans = f[1][M];
  auto merge = [&](mint s, vector<mint> vv) -> void {
    ans += s;
    for (int i = 0; i < sz(v); i++) {
      for (int j = 0; j < sz(vv); j++) {
        ans += f[i + j + 1][M] * v[i] * vv[j];
      }
    }
    for (int i = 0; i < sz(vv); i++) {
      if (i < sz(v)) v[i] += vv[i];
      else v.push_back(vv[i]);
    }
  };

  auto [ans_l, vl] = solvePerfect(N / 2, M);
  merge(ans_l, vl);
  merge(ans_l, vl);

  v.insert(v.begin(), 0);
  return memo[{N, M}] = {ans, v};
}

pair<mint, vector<mint>> solve(ll N, int M) {
  if (N == 0) return {0, {}};

  vector<mint> v = {1};
  mint ans = f[1][M];
  auto merge = [&](mint s, vector<mint> vv) -> void {
    ans += s;
    for (int i = 0; i < sz(v); i++) {
      for (int j = 0; j < sz(vv); j++) {
        ans += f[i + j + 1][M] * v[i] * vv[j];
      }
    }
    for (int i = 0; i < sz(vv); i++) {
      if (i < sz(v)) v[i] += vv[i];
      else v.push_back(vv[i]);
    }
  };

  ll Nl = 0, Nr = 0;
  int d = 0;
  while (Nl + (1LL << d) + Nr + (1LL << d) <= N-1) {
    Nl += 1LL << d;
    Nr += 1LL << d;
    d++;
  }
  ll left = (N-1) - (Nl + Nr);
  if (left <= (1LL << d)) {
    Nl += left;

    auto [ans_l, vl] = solve(Nl, M);
    merge(ans_l, vl);

    auto [ans_r, vr] = solvePerfect(Nr, M);
    merge(ans_r, vr);
  }
  else {
    Nl += 1LL << d;
    Nr += left - (1LL << d);

    auto [ans_l, vl] = solvePerfect(Nl, M);
    merge(ans_l, vl);

    auto [ans_r, vr] = solve(Nr, M);
    merge(ans_r, vr);
  }

  v.insert(v.begin(), 0);
  return {ans, v};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    ll N; cin >> N;
    int M; cin >> M;
    precompute(N, M);
    memo.clear();
    cout << solve(N, M).first << '\n';
  }
}
