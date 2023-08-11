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

int k, A, H;

mint powA[35];

// winner, hash w/o winner, has w/ winner, place
using T = tuple<int, mint, mint, vector<int>>;
T eval(vector<int> v, int mask, int p) {
  mint res = 0;
  int j = 0;
  vector<int> place(1 << k);
  while (sz(v) > 1) {
    vector<int> nv;
    for (int i = 0; i < sz(v); i += 2) {
      if (mask & (1 << j)) {
        nv.push_back(v[i]);
        res += v[i+1] * powA[p];
        place[v[i+1]-1] = p;
      }
      else {
        assert(i + 1 < sz(v));
        nv.push_back(v[i+1]);
        res += v[i] * powA[p];
        place[v[i]-1] = p;
      }
      j++;
    }
    p = (p - 1) / 2 + 1;
    v = nv;
  }
  place[v[0]-1] = p;
  return {v[0], res + v[0] * powA[p-1], res + v[0] * powA[p], place};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> k >> A >> H;
  powA[0] = 1;
  for (int i = 1; i < 35; i++) {
    powA[i] = mint(A) * powA[i-1];
  }
  if (k < 5) {
    vector<int> v(1 << k); iota(all(v), 1);
    int p = (1 << (k-1)) + 1;
    F0R(mask, 1 << ((1 << k) - 1)) {
      auto [winner, _, h, place] = eval(v, mask, p);
      // cout << mask << ' ' << place << ": " << h << endl;
      if (h == H) {
        for (auto x: place) {
          cout << x << ' ';
        }
        cout << '\n';
        return 0;
      }
    }
    cout << -1 << '\n';
  }
  else {
    vector<int> v1(1 << (k-1)); iota(all(v1), 1);
    vector<int> v2(1 << (k-1)); iota(all(v2), (1 << (k-1)) + 1);
    map<int, T> m1, m2;
    int p = (1 << (k-1)) + 1;
    F0R(mask, 1 << ((1 << (k-1)) - 1)) {
      auto [winner, h1, h2, place] = eval(v1, mask, p);
      m1[h2.val] = {winner, h1, h2, place};
    }
    F0R(mask, 1 << ((1 << (k-1)) - 1)) {
      auto [winner, h1, h2, place] = eval(v2, mask, p);
      m2[h2.val] = {winner, h1, h2, place};
    }
    for (auto [h, t]: m1) {
      auto [winner, h1, h2, place] = t;
      mint target = H - h1;
      if (m2.count(target)) {
        auto [a, b, c, place2] = m2[target];
        vector<int> ans(1 << k);
        F0R(i, 1 << k) ans[i] = place[i] + place2[i];
        ans[winner-1] = 1;
        ans[a-1] = 2;
        for (auto x: ans) {
          cout << x << ' ';
        }
        cout << '\n';
        return 0;
      }
    }
    for (auto [h, t]: m2) {
      auto [winner, h1, h2, place] = t;
      mint target = H - h1;
      if (m1.count(target)) {
        auto [a, b, c, place2] = m1[target];
        vector<int> ans(1 << k);
        F0R(i, 1 << k) ans[i] = place[i] + place2[i];
        ans[winner-1] = 1;
        ans[a-1] = 2;
        for (auto x: ans) {
          cout << x << ' ';
        }
        cout << '\n';
        return 0;
      }
    }
    cout << -1 << '\n';
  }
}
