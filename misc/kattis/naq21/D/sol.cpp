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

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

      mod_int() : val(0) {}
      mod_int(int _val) : val((_val+MOD) % MOD) {}

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
} //}}}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; getline(cin, s);
  int n = stoi(s);

  map<string, int> mp;
  int pt = 0;
  auto getId = [&](string s) {
    return mp.count(s) ? mp[s] : mp[s] = pt++;
  };

  vector<vector<mint>> A;
  F0R(i, n) {
    getline(cin, s);
    stringstream ss(s);
    int c = 1;
    bool pastEq = false;
    string x;

    vector<mint> v(110);
    while (ss >> x) {
      if (x == "*") c = !pastEq ? 1 : -1;
      else if (x == "/") c = !pastEq ? -1 : 1;
      else if (x == "=") {
        c = -1;
        pastEq = true;
      }
      else if (x != "1") {
        int id = getId(x);
        v[id] += c;
      }
    }
    A.push_back(v);
  }


  // Gaussian elimination
  int N = sz(A);
  int M = sz(A[0])-1;
  vector<int> where(M, -1);
  for (int row = 0, col = 0; row < N && col < M; col++) {
    int nr = -1;
    for (int i = row; i < N; i++) if (A[i][col] != mint(0)) {
      nr = i;
      break;
    }
    if (nr == -1) continue;
    else {
      for (int j = col; j <= M; j++) swap(A[row][j], A[nr][j]);
 
      for (int i = 0; i < N; i++) {
        if (i == row || A[i][col] == 0) continue;
        mint t = A[i][col] / A[row][col]; // divide by A[row][col]
        for (int j = col; j <= M; j++) {
          A[i][j] -= A[row][j] * t;
        }
      }
      where[col] = row;
      row++;
    }
  }

  // Check if there is an equation with exactly one nonzero coefficient (meaning that this variable equals 0)
  F0R(i, N) {
    int cnt = 0;
    F0R(j, M) {
      if (A[i][j] != 0) cnt++;
    }
    if (cnt == 1) {
      cout << "invalid\n";
      return 0;
    }
  }
  cout << "valid\n";
}
