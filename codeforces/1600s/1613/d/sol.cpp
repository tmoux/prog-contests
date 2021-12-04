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

bool mex_correct(vector<int> v) {
  auto mex = [](const set<int>& s) -> int {
    int i = 0;
    while (true) {
      if (!s.count(i)) return i;
      else i++;
    }
    assert(false);
  };
  set<int> s;
  for (int i = 0; i < sz(v); i++) {
    s.insert(v[i]);
    //cout << i << ' ' << s << ": " << mex(s) << endl;
    if (abs(v[i] - mex(s)) <= 1) {

    }
    else return false;
  }
  return true;
};
const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void mult2(int& a) {
  a = mult(a, 2);
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

int solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto& i: a) cin >> i;
  vector<int> dp1(n+2, 0), dp2(n+2, 0);
  dp1[0] = 1;
  for (int i: a) {
    madd(dp1[i+1], dp1[i+1]);
    madd(dp1[i+1], dp1[i]);
    if (i > 0) madd(dp2[i-1], dp2[i-1]);
    if (i > 0) madd(dp2[i-1], dp1[i-1]);
    madd(dp2[i+1], dp2[i+1]);
  }

  int ans = M-1;
  for (int i = 0; i < n+2; i++) {
    madd(ans, dp1[i]);
    madd(ans, dp2[i]);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  /*
  F0R(i1, 6) {
  F0R(i2, 6) {
  F0R(i3, 6) {
  F0R(i4, 6) {
  F0R(i5, 6) {
  F0R(i6, 6) {
    vector<int> v = {i1, i2, i3, i4, i5, i6};
    if (mex_correct(v)) {
      cout << v << '\n';
    }
  }}}}}}
  return 0;
  */
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
