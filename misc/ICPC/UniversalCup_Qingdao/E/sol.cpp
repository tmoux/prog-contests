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

string op(string s) {
  string t(sz(s), '#');
  F0R(i, sz(s)) {
    if (s[i] == '0') t[i] = s[(i+1)%sz(s)];
    else t[i] = s[(i-1+sz(s))%sz(s)];
  }
  return t;
}

string shift(string s) {
  return s.back() + s.substr(0, sz(s)-1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // int N; cin >> N;
  // int k; cin >> k;
  // map<string, int> mp;
  // int c = 0;
  // F0R(mask, 1 << N) {
  //   string t;
  //   F0R(i, N) {
  //     if (mask & (1 << i)) t += '1';
  //     else t += '0';
  //   }
  //   mp[t] = c++;
  // }
  // F0R(mask, 1 << N) {
  //   string t;
  //   F0R(i, N) {
  //     if (mask & (1 << i)) t += '1';
  //     else t += '0';
  //   }
  //   string u = op(t);
  //   if (__builtin_popcount(mask) == k)
  //     cout << t << ' ' << u << endl;
  // }
  // return 0;
  string s; cin >> s;
  string orig = s;
  REP(sz(s)+1) {
    cout << s << endl;
    if (s == shift(op(s))) break;
    // s = op(s);
    s = shift(op(s));
  }
}
