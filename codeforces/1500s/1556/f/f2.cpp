#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

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
  friend mod_int operator^(const mod_int& a, const mod_int& b) {
    return a ^ b.val;
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

const int MOD = 1e9+7;
using mint = mod_int<MOD>;

int n, a[maxn];
mint p[maxn][maxn];

mint all_beaten_dp[1<<maxn][maxn];
mint all_beaten(int mask, int j) {
  mint& res = all_beaten_dp[mask][j];
  if (res != -1) return res;
  res = mod_int(1);
  F0R(i, n) {
    if (mask & (1<<i))
      res *= p[i][j];
  }
  return res;
}

mint all_beats(int mask1, int mask2) {
  mint res = mod_int(1);
  F0R(i, n) {
    if (mask2 & (1<<i))
      res *= all_beaten(mask1, i);
  }
  return res;
}

mint strong_dp[1<<maxn];
int strong(int mask) {
  int& res = strong_dp[mask];
  if (res != -1) return res;
  res = 1;
  for (int submask = mask; submask; submask = (submask-1) & mask) {
    if (submask == mask) continue;
    msub(res, mult(strong(submask), all_beats(submask, mask^submask)));
  }
  return res;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
}
