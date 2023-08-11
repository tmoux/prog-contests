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

string flip(string s) {
  for (char& c: s) {
    c = c == '+' ? '-' : '+';
  }
  return s;
}

vector<string> f(int n) {
  if (n == 1) {
    return {"+"};
  }
  vector<string> ret;
  for (int i = 1; i < n; i++) {
    auto v = f(i);
    auto u = f(n - i);

    for (auto s: v) {
      auto ss = flip(s);
      for (auto t: u) {
        ret.push_back(ss + t);
      }
    }
  }
  sort(all(ret)); ret.erase(unique(all(ret)), ret.end());
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    int x; cin >> x;
    A[i] = 1 << x;
  }
  vector<int> v;
  F0R(mask, 1 << N) {
    int sum = 0;
    F0R(i, N) {
      sum += (mask & (1 << i)) ? A[i] : -A[i];
    }
    v.push_back(sum);
  }
  sort(all(v)); v.erase(unique(all(v)), v.end());
  cout << v << endl;

  int mx = 0;
  F0R(i, N) {
    mx += A[i];
  }
  DEBUG(mx);
  sort(all(A), greater());
  int mn = 0;
  for (auto x: A) {
    if (mn - x >= 0) mn -= x;
    else mn += x;
  }
  DEBUG(mn);



  // auto v = f(N);
  // for (auto s: v) {
  //   cout << s << '\n';
  // }
}
