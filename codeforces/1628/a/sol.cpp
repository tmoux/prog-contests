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

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto& i: a) cin >> i;
  vector<int> suffixMex(n);
  {
    vector<bool> seen(n+1, false);
    int mex = 0;
    for (int i = n-1; i >= 0; i--) {
      seen[a[i]] = true;
      while (seen[mex]) mex++;
      suffixMex[i] = mex;
    }
  }
  int i = 0;
  vector<int> b;
  vector<bool> seen(n+1, false);
  while (i < n) {
    int nextElt = suffixMex[i];
    seen[a[i]] = true;
    int mex = 0; while (seen[mex]) mex++;
    int j = i+1;
    while (mex < nextElt) {
      assert(j < n);
      seen[a[j]] = true;
      while (seen[mex]) mex++;
      j++;
    }
    b.push_back(nextElt);
    for (int k = i; k < j; k++) seen[a[k]] = false;
    i = j;
  }

  // output
  cout << sz(b) << '\n';
  for (auto x: b) {
    cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
