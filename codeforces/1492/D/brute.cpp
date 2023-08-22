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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  auto cnt = [](int x) -> pair<int, int> {
    int a = 0, b = 0;
    while (x) {
      if (x&1) b++;
      else a++;
      x >>= 1;
    }
    return {a, b};
  };
  int a, b; cin >> a >> b;
  int K = a + b;

  set<int> ks;
  F0R(i, 1 << K) {
    auto ci = cnt(i);
    if (ci == make_pair(a, b)) {
      F0R(j, i+1) {
        auto cj = cnt(j);
        if (cj == make_pair(a, b)) {
          int z = i - j;
          int k = __builtin_popcount(z);
          if (k == a+b-2) {
            cout << k << ": " << bitset<15>(i) << ' ' << bitset<15>(j) << ' ' << bitset<15>(i-j) << endl;
          }
          // if (!ks.count(k)) {
          //   cout << k << ": " << bitset<10>(i) << ' ' << bitset<10>(j) << ' ' << bitset<10>(i-j) << endl;
          // }
          // ks.insert(k);
        }
      }
    }
  }
  cout << ks << endl;
}
