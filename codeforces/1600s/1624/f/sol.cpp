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

int ask(int c) {
  cout << "+ " << c << endl;
  int z; cin >> z;
  return z;
}

int answer(int x) {
  cout << "! " << x << endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  int lo = 1, hi = n-1;
  int modLo = 1, modHi = n-1;
  int z;

  int cur = 0;
  int added = 0;
  while (lo < hi) {
    // DEBUG(lo);
    // DEBUG(hi);
    // cout << modLo << ' ' << modHi << endl;
    pair<int,int> best = {-1, -1};
    for (int i = 1; i < n; i++) {
      int L = (modLo + i) % n;
      int R = (modHi + i) % n;
      if (L > R) {
        int rt = R + 1;
        int lt = (hi-lo+1)-rt;
        ckmax(best, {min(lt, rt), i});
      }
    }
    // cout << best << endl;
    int c = best.second;
    z = ask(c);
    added += c;
    if (z == cur) {
      hi = lo-1;
      for (int i = modLo; i != modHi; i = (i+1)%n) {
        if (i+c < n) {
          hi++;
        }
        else break;
      }
    }
    else {
      cur++;
      lo = hi+1;
      for (int i = modHi; i != modLo; i = (i+n-1)%n) {
        if (i+c >= n) {
          lo--;
        }
        else break;
      }
    }
    modLo = (lo+added) % n;
    modHi = (hi+added) % n;
  }
  answer(lo+added);
}
