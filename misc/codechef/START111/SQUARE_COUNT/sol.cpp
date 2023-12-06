#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

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
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

// combine should be associative and idempotent (e.g., min, max, gcd)
template<typename T, T (*combine)(T, T)>
struct SparseTable
{
  int n, maxk;
  vector<vector<T>> tb;
  static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
  SparseTable() {}
  SparseTable(const vector<T>& a) : n(sz(a)) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    tb.resize(maxk, vector<int>(n));
    for (int i = 0; i < n; i++) tb[0][i] = a[i];
    for (int k = 1; k <= lg(n); k++) {
      for (int i = 0; i < n; i++) {
        int nx = i + (1<<(k-1));
        if (nx < n) tb[k][i] = combine(tb[k-1][i], tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  T prod(int l, int r) {
    int g = lg(r-l+1);
    return combine(tb[g][l], tb[g][r-(1<<g)+1]);
  }
};

int gcdcomp(int x, int y) {
  return std::gcd(x, y);
}

// Iterate over split point i.
// For a fixed endpoint, gcd only changes log(n) times.
// Thus sufficient to iterate over all ranges, and store map of hashes of (normalized) gcd

const int maxn = 1e7+7;
uint64_t hsh[maxn], core[maxn];
int spf[maxn];

vector<int> pr;
void init_spf() {
  spf[1] = 1;
  for (int i=2; i < maxn; ++i) {
    if (spf[i] == 0) {
      spf[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] < maxn; ++j) {
      spf[i * pr[j]] = pr[j];
      if (pr[j] == spf[i]) {
        break;
      }
    }
  }
}

mint solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  SparseTable<int, gcdcomp> st(A);

  auto find_left = [&](int l, int r) -> int {
    int g = st.prod(l, r);
    int lo = -1, hi = l;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (st.prod(mid, r) == g ? hi : lo) = mid;
    }
    return hi;
  };
  auto find_right = [&](int l, int r) -> int {
    int g = st.prod(l, r);
    int lo = r, hi = N;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (st.prod(l, mid) == g ? lo : hi) = mid;
    }
    return lo;
  };

  map<uint64_t, mint> mp;
  mint ans = 0;
  F0R(i, N) {
    // add to ans
    int j = i;
    while (j < N) {
      int nj = find_right(i, j);
      uint64_t h = core[st.prod(i, nj)];
      mint matches = mp.count(h) ? mp[h] : mint(0);
      ans += matches * (nj - j + 1);
      j = nj + 1;
    }

    // update
    j = i;
    while (j >= 0) {
      int nj = find_left(j, i);
      mp[core[st.prod(nj, i)]] += j - nj + 1;
      j = nj - 1;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  for (int x = 1; x < maxn; x++) hsh[x] = rng();
  for (int x = 1; x < maxn; x++) {
    core[x] = 0;
    int y = x;
    while (y > 1) {
      int p = spf[y];
      core[x] ^= hsh[p];
      y /= p;
    }
  }
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
