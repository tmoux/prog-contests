#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) 
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
void msub(int& a, int b) {
  madd(a, M-b);
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
const int maxn = 2e5+5;
int fac[maxn], ifac[maxn];

int comb(int n, int k) {
  if (n < k) return 0;
  int ans = fac[n];
  ans = mult(ans, ifac[k]);
  ans = mult(ans, ifac[n-k]);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fac[i] = mult(fac[i-1], i);
    ifac[i] = inverse(fac[i]);
  }

  int n; cin >> n;
  vector<int> a(n);
  vector<int> lsb_count(30);
  for (auto& i: a) {
    cin >> i;
    for (int k = 0; k < 30; k++) {
      if (i & (1<<k)) {
        lsb_count[k]++;
        break;
      }
    }
  }

  int S = n - lsb_count[0];
  int bad = 0;
  for (int i = 1; i < 30; i++) {
    S -= lsb_count[i];
    for (int j = 1; j <= lsb_count[i]; j += 2) {
      madd(bad, mult(comb(lsb_count[i], j), modexp(2, S)));
    }
  }

  int tot = modexp(2, n);
  msub(tot, 1);
  msub(tot, bad);
  cout << tot << '\n';
}
