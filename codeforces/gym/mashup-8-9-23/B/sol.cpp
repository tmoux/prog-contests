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
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M, K; cin >> N >> M >> K;

  int bad_rows = 0, bad_cols = 0;
  int invalid_rows = 0, invalid_cols = 0;
  array<int, 2> checkerboard_cnt = {0, 0};
  vector<array<int, 2>> cnt_row(N, {0, 0}), cnt_col(M, {0, 0});
  map<pair<int, int>, int> G;

  auto getans = [&]() -> mint {
    mint ans = 0;
    if (invalid_rows == 0) {
      ans += mint(2) ^ (N - bad_rows);
    }
    if (invalid_cols == 0) {
      ans += mint(2) ^ (M - bad_cols);
    }
    F0R(i, 2) if (checkerboard_cnt[i] == 0) ans -= 1;
    return ans;
  };

  auto add_checkerboard = [&](int p, int d) {
    checkerboard_cnt[p] += d;
  };

  auto is_invalid = [&](array<int, 2> a) {
    return a[0] > 0 && a[1] > 0;
  };

  auto add_row = [&](int r, int p, int d) {
    auto pre = cnt_row[r];
    cnt_row[r][p] += d;
    auto cur = cnt_row[r];
    if (pre[0] == 0 && pre[1] == 0) {
      bad_rows++;
    }
    else if (cur[0] == 0 && cur[1] == 0) {
      bad_rows--;
    }
    if (!is_invalid(pre) && is_invalid(cur)) {
      invalid_rows++;
    }
    else if (is_invalid(pre) && !is_invalid(cur)) {
      invalid_rows--;
    }
  };

  auto add_col = [&](int c, int p, int d) {
    auto pre = cnt_col[c];
    cnt_col[c][p] += d;
    auto cur = cnt_col[c];
    if (pre[0] == 0 && pre[1] == 0) {
      bad_cols++;
    }
    else if (cur[0] == 0 && cur[1] == 0) {
      bad_cols--;
    }
    if (!is_invalid(pre) && is_invalid(cur)) {
      invalid_cols++;
    }
    else if (is_invalid(pre) && !is_invalid(cur)) {
      invalid_cols--;
    }
  };

  auto update_set = [&](int i, int j, int t) -> void {
    assert(!G.count({i, j}));
    G[{i, j}] = t;
    int p = (i ^ j ^ G[{i, j}]) & 1;
    add_checkerboard(p, 1);
    add_row(i, p, 1);
    add_col(j, p, 1);
  };

  auto update_unset = [&](int i, int j) -> void {
    if (!G.count({i, j})) return;
    int p = (i ^ j ^ G[{i, j}]) & 1;
    add_checkerboard(p, -1);
    add_row(i, p, -1);
    add_col(j, p, -1);
    G.erase({i, j});
  };

  while (K--) {
    int x, y, t; cin >> x >> y >> t;
    x--, y--;
    update_unset(x, y);
    if (t != -1) update_set(x, y, t);
    cout << getans() << '\n';
  }
}
