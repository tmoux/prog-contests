#include "bits/stdc++.h"
#include <cstdlib>
using namespace std;

template<const int &MOD>
struct _m_int {
    int val;
 
    _m_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
 
    _m_int(uint64_t v) {
        if (v >= MOD) v %= MOD;
        val = int(v);
    }
 
    _m_int(int v) : _m_int(int64_t(v)) {}
    _m_int(unsigned v) : _m_int(uint64_t(v)) {}
 
    static int inv_mod(int a, int m = MOD) {
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
        int g = m, r = a, x = 0, y = 1;
 
        while (r != 0) {
            int q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }
 
        return x < 0 ? x + m : x;
    }
 
    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }
 
    _m_int& operator+=(const _m_int &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    _m_int& operator-=(const _m_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
 
    _m_int& operator*=(const _m_int &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }
 
    _m_int& operator/=(const _m_int &other) {
        return *this *= other.inv();
    }
 
    friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
    friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
    friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
    friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }
 
    _m_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }
 
    _m_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }
 
    _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
    _m_int operator--(int) { _m_int before = *this; --*this; return before; }
 
    _m_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }
 
    friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
    friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
    friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
    friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
    friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
    friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }
 
    _m_int inv() const {
        return inv_mod(val);
    }
 
    _m_int pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);
 
        _m_int a = *this, result = 1;
 
        while (p > 0) {
            if (p & 1)
                result *= a;
 
            p >>= 1;
 
            if (p > 0)
                a *= a;
        }
 
        return result;
    }
 
    friend ostream& operator<<(ostream &os, const _m_int &m) {
        return os << m.val;
    }

    friend istream& operator>>(istream &is, _m_int &m) {
      int64_t x;
      is >> x;
      m = _m_int(x);
      return is;
    }
};

const int MOD = 998244353;
using mod_int = _m_int<MOD>;

// Source: Lain
// Tested on: https://judge.yosupo.jp/problem/matrix_det, https://judge.yosupo.jp/problem/inverse_matrix
// 
// Matrix class for general applications
template <typename T>
struct Matrix {
  public:
    Matrix() = default;
    Matrix(int n, int m) : n(n), m(m), A(n, vector<T>(m,T())) {}

    static Matrix I(int n) {
      Matrix identity(n,n);
      for (int i = 0; i < n; i++)
        identity[i][i] = 1;
      return identity;
    }

    int N() const { return A.size(); }
    int M() const { return A[0].size(); }

    vector<T>& operator[] (int index) { return A[index]; }
    const vector<T>& operator[] (int index) const { return A[index]; }

    Matrix& operator+=(const Matrix& B) {
      int n = N(), m = M();
      assert(n == B.N() && m == B.M());
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          (*this)[i][j] += B[i][j];
      return *this;
    }

    Matrix& operator-=(const Matrix& B) {
      int n = N(), m = M();
      assert(n == B.N() && m == B.M());
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          (*this)[i][j] -= B[i][j];
      return *this;
    }

    Matrix& operator*=(const Matrix& B) {
      int n = N(), m = M();
      int bn = B.N(), bm = B.M();
      assert(m == bn);
      vector<vector<T>> C(n,vector<T>(bm,T()));
      for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++) 
          for (int j = 0; j < bm; j++)
            C[i][j] += (*this)[i][k]*B[k][j];
      A.swap(C);
      return *this;
    }

    Matrix& operator*=(const T& a) {
      int n = N(), m= M();
      for (int i =0 ; i < n; i++)
        for (int j =0 ; j < m; j++)
          (*this)[i][j] *= a;
      return *this;
    }

    Matrix& operator/=(const T& a) {
      int n = N(), m= M();
      for (int i =0 ; i < n; i++)
        for (int j =0 ; j < m; j++)
          (*this)[i][j] /= a;
      return *this;
    }

    bool operator==(const Matrix& B) const {
      int n = N(), m = M();
      if (n != B.N() || m != B.M()) return false;
      for (int i = 0; i < n; i++) 
        for (int j  = 0; j < m; j++)
          if (A[i][j] != B[i][j])
            return false;
      return true;
    }

    bool operator!=(const Matrix& B) const {
      int n = N(), m = M();
      if (n != B.N() || m != B.M()) return true;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          if (A[i][j] != B[i][j])
            return true;
      return false;
    }

    friend ostream &operator<<(ostream& os, const Matrix& A) {
      int n = A.N(), m = A.M();
      os << "Matrix with dimensions " << n << "x" << m << '\n';
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
          os << A[i][j] << " ";
        os << '\n';
      }
      return os;
    }

    friend istream &operator>>(istream& is, Matrix& A) {
      for (auto& row : A.A)
        for (auto& col : row)
          is >> col;
      return is;
    }

    friend vector<T> operator*(const Matrix& A, const vector<T>& v) {
      int n = A.N(), m = A.M();
      assert(m == v.size());
      vector<T> ret(n);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ret[i] += A[i][j] * v[j];
      return ret;
    }

    friend vector<T> operator*(const vector<T>& v, const Matrix& A) {
      int n = A.N(), m = A.M();
      assert(n == v.size());
      vector<T> ret(m);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ret[j] += A[i][j] * v[j];
      return ret;
    }

    Matrix operator+(const Matrix& B) const { return (Matrix(*this) += B); }
    Matrix operator-(const Matrix& B) const { return (Matrix(*this) -= B); }
    Matrix operator*(const Matrix& B) const { return (Matrix(*this) *= B); }
    Matrix operator*(const T& a) const { return (Matrix(*this) *= a); }
    Matrix operator/(const T& a) const { return (Matrix(*this) /= a); }

    Matrix pow(int64_t k) const {
      Matrix B = Matrix::I(N());
      bool is_identity = true;
      if (k == 0) return B;
      for (int i = 63 - __builtin_clzll(k); i >= 0; i--) {
        if (!is_identity) B *= B;
        if ((k>>i)&1) {
          B *= (*this);
          is_identity = false;
        }
      }
      return B;
    }

    Matrix transpose() const {
      int n = N(), m = M();
      Matrix B(n,m);
      for (int i = 0; i < n; i++)
        for (int j =0; j < m; j++)
          B[i][j] = A[j][i];
      return B;
    }

    int inverse() {
      int n = N(), m = M();
      assert(n == m);
      int rank = 0;
      Matrix ret = Matrix::I(n), tmp = *this;
      for (int i = 0; i < n; i++) {
        int ptr = i;
        while(ptr < n && tmp[ptr][i] == 0) ptr++;
        if (ptr == n) continue;
        rank++;
        ret[i].swap(ret[ptr]), tmp[i].swap(tmp[ptr]);
        T inv = T(1)/tmp[i][i];
        for (int j = 0; j < m; j++)
          ret[i][j] *= inv;
        for (int j = i+1; j < m; j++)
          tmp[i][j] *= inv;
        for (int h = 0; h < n; h++) {
          if (i == h) continue;
          const T c = -tmp[h][i];
          for (int j = 0; j < m; j++)
            ret[h][j] += ret[i][j]*c;
          for (int j = i+1; j < m; j++)
            tmp[h][j] += tmp[i][j]*c;
        }
      }
      swap(A,ret.A);
      return rank;
    }

    T determinant() {
      int n = N(), m = M();
      assert(n == m);
      Matrix B(*this);
      T prod = 1;
      for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = i; j < n; j++) {
          if (B[j][i] != 0) {
            idx = j;
            break;
          }
        }
        if (idx == -1) return 0;
        if (i != idx) {
          prod *= T(-1);
          swap(B[i], B[idx]);
        }
        prod *= B[i][i];
        T inv = T(1)/B[i][i];
        for (int j = 0; j < n; j++)
          B[i][j] *= inv;
        for (int j = i+1; j < n; j++) {
          T a = B[j][i];
          if (a== 0) continue;
          for (int k = i; k < m; k++)
            B[j][k] -= B[i][k]*a;
        }
      }
      return prod;
    }

    // Gauss-Jordan elimination

    // Choose largest pivot in the case of R, any non-zero pivot in the case of Z_p
    template<typename U, typename std::enable_if<std::is_floating_point<U>::value>::type * = nullptr>
      static int choose_pivot(const Matrix<U>& B, int h, int curr) noexcept {
        int n = B.N();
        int piv = -1;
        for (int j = h; j < n; j++) {
          if (B[j][curr] && (piv < 0 || abs(B[j][curr]) > abs(B[piv][curr])))
            piv = j;
        }
        return piv;
      }

    template<typename U, typename std::enable_if<!std::is_floating_point<U>::value>::type * = nullptr>
      static int choose_pivot(const Matrix<U>& B, int h, int curr) noexcept {
        int n = B.N();
        for (int j = h; j < n; j++) {
          if (B[j][curr] != 0) return j;
        }
        return -1;
      }

    Matrix gauss_jordan() const {
      int n = N(), m = M();
      int c = 0;
      Matrix B(*this);
      vector<int> ws;
      ws.reserve(m);
      for (int i = 0; i < n; i++) {
        if (c == m) break;
        int piv = choose_pivot(B,i,c);
        if (piv == -1) {
          c++;
          i--;
          continue;
        }
        if (i != piv) {
          for (int j = 0; j < m; j++) {
            swap(B[i][j],B[piv][j]);
            B[piv][j] *= -1;
          }
        }
        ws.clear();
        for (int j = c; j < m; j++)
          if (B[i][j] != 0)
            ws.emplace_back(j);
        const T hcinv = T(1)/B[i][c];
        for (int k = 0; k < n; k++) {
          if (i != k) {
            const T coeff = B[k][c]*hcinv;
            for (auto& w : ws) {
              B[k][w] -= B[i][w]*coeff;
              B[k][c] = 0;
            }
          }
        }
        c++;
      }
      return B;
    }

  private:
    size_t n, m;
    vector<vector<T>> A;
};

template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}

// Source: hitonanode
// Tested on: https://judge.yosupo.jp/problem/system_of_linear_equations
// Solve a system of linear equations
// Returns {{},{}} if no solution
// Otherwise returns {solution, basis of solution space}
// Rank = |basis of solution space|
template <typename T>
pair<vector<T>, vector<vector<T>>> system_of_linear_equations(Matrix<T> A, vector<T> b) {
  int n = A.N(), m = A.M();
  Matrix<T> M(n, m + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) M[i][j] = A[i][j];
    M[i][m] = b[i];
  }
  M = M.gauss_jordan();
  cout << M << endl;
  vector<int> ss(m, -1);
  for (int i = 0; i < n; i++) {
    int j = 0;
    while (j <= m and M[i][j] == 0) j++;
    if (j == m) { // No solution
      return {{}, {}};
    }
    if (j < m) ss[j] = i;
  }
  cout << ss << endl;
  vector<T> x(m);
  vector<std::vector<T>> D;
  for (int j = 0; j < m; j++) {
    if (ss[j] == -1) {
      std::vector<T> d(m);
      d[j] = 1;
      for (int jj = 0; jj < j; jj++) {
        if (ss[jj] != -1) d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];
      }
      D.emplace_back(d);
    } else
      x[j] = M[ss[j]][m] / M[ss[j]][j];
  }
  return make_pair(x, D);
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n,m;
  cin >> n >> m;
  Matrix<mod_int> A(n,m);
  cin >> A;
  vector<mod_int> b(n);
  for (auto& x : b) cin >> x;
  auto res = system_of_linear_equations(A,b);
  if (res.first.empty()) {
    cout << -1 << '\n';
  }
  else {
    cout << res.second.size() << '\n';
    for (auto& x : res.first) cout << x << " ";
    cout << '\n';

    for (auto& v : res.second) {
      for (auto& e : v) cout << e << " ";
      cout << '\n';
    }
  }

}


