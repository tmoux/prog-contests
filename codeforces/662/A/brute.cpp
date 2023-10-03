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

template<typename T = uint32_t, int LOG_A = 30>
struct XorBasis {
  T basis[LOG_A];
  int basis_size = 0;
  int num_vectors = 0;
  XorBasis() {
    fill(basis, basis+LOG_A, 0);
  }

  T getBit(T x, int i) {
    return x & (1LL << i);
  }

  void insertVector(T mask) {
    if (!mask) return;
    num_vectors++;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (!getBit(mask, i)) continue;
      if (!basis[i]) {
        basis[i] = mask;
        basis_size++;
        return;
      }
      mask ^= basis[i];
    }
  }

  bool inSpan(T x) { // check if x is in the span of the basis
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (basis[i] && getBit(x, i)) x ^= basis[i];
    }
    return x == 0;
  }

  T maxXor(T x) { // maximum z s.t. x ^ y = z, where y in span
    T ans = x;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (basis[i] && !getBit(ans, i)) ans ^= basis[i];
    }
    return ans;
  }

  T minXor(T x) { // maximum z s.t. x ^ y = z, where y in span
    T ans = x;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (basis[i] && !getBit(ans, i)) ans ^= basis[i];
    }
    return ans;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  XorBasis<uint64_t, 60> xb;
  int N; cin >> N;
  uint64_t x = 0;
  F0R(i, N) {
    uint64_t a, b; cin >> a >> b;
    x ^= a;
    xb.insertVector(a ^ b);
    cout << "inserting " << (a^b) << endl;
  }
  cout << "checking " << x << endl;
  if (!xb.inSpan(x)) {
    cout << "1/1" << '\n';
  }
  else {
    int D = xb.basis_size;
    DEBUG(D);
    cout << ((1LL << D) - 1) << "/" << (1LL << D) << '\n';
  }
}
