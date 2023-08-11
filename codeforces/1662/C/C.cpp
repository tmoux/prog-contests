#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

const int maxn = 205;
int N, M, K;

struct Matrix {
  int n, m;
  mint a[maxn][maxn];
  Matrix(int _n, int _m) {
    n = _n;
    m = _m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a[i][j] = 0;
      }
    }
  }

  Matrix operator*(Matrix r) {
    assert(m == r.n);
    Matrix res(n, r.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < r.m; j++) {
        for (int k = 0; k < m; k++) {
          res.a[i][j] += a[i][k] * r.a[k][j];
        }
      }
    }
    return res;
  }
};

Matrix operator^(Matrix r, int b) {
  assert(r.n == r.m);
  Matrix res(r.n, r.m);
  for (int i = 0; i < r.n; i++) res.a[i][i] = 1;

  while (b) {
    if (b&1) res = res * r;
    r = r * r;
    b >>= 1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;

  Matrix A(2*N, 2*N);
  for (int i = 0; i < N; i++) {
    A.a[i+N][i] = 1;
    A.a[i][i+N] = 1;
  }
  Matrix G(N, N);
  for (int i = 0; i < M; i++) {
    int x, y; cin >> x >> y;
    x--; y--;
    A.a[x][y] = A.a[y][x] = 1;
    A.a[x][x+N]--;
    A.a[y][y+N]--;

    G.a[x][y] = G.a[y][x] = 1;
  }
  A = A ^ (K-1);

  Matrix B(2*N, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      B.a[i+N][j] = G.a[i][j];
      if (G.a[i][j] != 0) {
        B.a[i][i]--;
      }
    }
  }
  G = G ^ 2;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      B.a[i][j] += G.a[i][j];
    }
  }

  Matrix res = A * B;

  for (int i = 0; i < 2*N; i++) {
    for (int j = 0; j < N; j++) {
    }
  }
  mint ans = 0;
  for (int i = 0; i < N; i++) {
    ans += res.a[i+N][i];
  }
  cout << ans << '\n';
}
