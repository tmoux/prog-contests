#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

      constexpr mod_int() : val(0) {}
      constexpr mod_int(int _val) : val(_val % MOD) {}

      constexpr mod_int operator+() const {
        return mod_int(val); 
      }
      constexpr mod_int operator-() const {
        return mod_int(MOD-val); 
      }
      constexpr mod_int inverse() const {
        assert(val != 0);
        return *this ^ (MOD - 2);
      }

      constexpr bool operator==(const mod_int& b) const {
        return val == b.val;
      }

      constexpr bool operator!=(const mod_int& b) const {
        return !(*this == b);
      }

      constexpr mod_int& operator+=(const mod_int& b) {
        val += b.val;
        if (val >= MOD) val -= MOD;
        return *this;
      }
      constexpr mod_int& operator-=(const mod_int& b) {
        return *this += -b;
      }
      constexpr mod_int& operator*=(const mod_int& b) {
        val = (1LL*val*b.val) % MOD;
        return *this;
      }
      constexpr mod_int& operator/=(const mod_int& b) {
        val = (1LL*val*b.inverse().val) % MOD;
        return *this;
      }

      constexpr mod_int& operator+=(int b) {
        return *this += mod_int(b);
      }
      constexpr mod_int& operator-=(int b) {
        return *this -= mod_int(b);
      }
      constexpr mod_int& operator*=(int b) {
        return *this *= mod_int(b);
      }
      constexpr mod_int& operator/=(int b) {
        return *this /= mod_int(b);
      }

      constexpr friend mod_int operator+(const mod_int& a, const mod_int& b) {
        mod_int c = a; c += b;
        return c;
      }
      constexpr friend mod_int operator-(const mod_int& a, const mod_int& b) {
        mod_int c = a; c -= b;
        return c;
      }
      constexpr friend mod_int operator*(const mod_int& a, const mod_int& b) {
        mod_int c = a; c *= b;
        return c;
      }
      constexpr friend mod_int operator/(const mod_int& a, const mod_int& b) {
        mod_int c = a; c /= b;
        return c;
      }

      constexpr friend mod_int operator^(mod_int a, int b) {
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<mint>> A(N, vector<mint>(M+1));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> A[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    cin >> A[i][M];
  }

  vector<int> where(M, -1);
  for (int row = 0, col = 0; row < N && col < M; col++) {
    int nr = -1;
    for (int i = row; i < N; i++) if (A[i][col] != mint(0)) {
      nr = i; break;
    }
    if (nr == -1) continue;
    else {
      for (int j = col; j <= M; j++) swap(A[row][j], A[nr][j]);
      /*
      mint x = A[row][col];
      for (int j = col; j <= M; j++) {
        A[row][j] /= x;
      }
      */
      for (int i = 0; i < N; i++) {
        if (i == row) continue;
        if (A[i][col] == 0) continue;
        mint t = A[i][col] / A[row][col]; // divide by A[row][col]
        for (int j = col; j <= M; j++) {
          A[i][j] -= A[row][j] * t;
        }
      }
      where[col] = row;
      row++;
    }
  }

  // check if impossible
  bool poss = true;
  for (int i = 0; i < N; i++) {
    if (all_of(A[i].begin(), A[i].begin()+M, [](auto x){return x == 0;}) && A[i].back() != 0) {
      poss = false;
      break;
    }
  }
  if (poss) {
    vector<vector<mint>> basis;
    vector<mint> x(M);
    for (int j = 0; j < M; j++) {
      if (where[j] == -1) {
        vector<mint> d(M);
        d[j] = 1;
        for (int jj = 0; jj < j; jj++) {
          if (where[jj] != -1) d[jj] = - A[where[jj]][j] / A[where[jj]][jj];
        }
        basis.push_back(d);
      }
      else x[j] = A[where[j]][M] / A[where[j]][j];
    }
    /*
    vector<mint> ans(M, -1);
    for (int i = M-1; i >= 0; i--) {
      if (where[i] == -1) {
        ans[i] = 0;
      }
      else {
        int t = where[i];
        ans[i] = A[t][M];
        for (int j = i+1; j < M; j++) {
          ans[i] -= ans[j] * A[t][j];
        }
      }
    }
    */
    cout << sz(basis) << '\n';
    for (int i = 0; i < M; i++) {
      cout << x[i] << ' ';
    }
    cout << '\n';

    for (auto v: basis) {
      for (auto e: v) {
        cout << e << ' ';
      }
      cout << '\n';
    }

    cout << "---\n";
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= M; j++) {
        cout << min(A[i][j].val, MOD-A[i][j].val) << ' ';
      }
      cout << '\n';
    }
  }
  else {
    cout << -1 << '\n';
  }
}
