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

void solve() {
  int n, m; cin >> n >> m;

  map<string, array<int, 3>> l2, l3;
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    for (int l = 0; l + 2 <= m; l++) {
      l2[s.substr(l,2)] = {l+1, l+1+1, i};
    }
    for (int l = 0; l + 3 <= m; l++) {
      l3[s.substr(l,3)] = {l+1, l+2+1, i};
    }
  }
  string s; cin >> s;
  vector<int> prev(m, -2);
  vector<array<int, 3>> ans(m);
  for (int i = 0; i < m; i++) {
    if (i == 0 || prev[i-1] != -2) {
      if (l2.count(s.substr(i, 2))) {
        prev[i+1] = i-1;
        ans[i+1] = l2[s.substr(i, 2)];
      }
      if (l3.count(s.substr(i, 3))) {
        prev[i+2] = i-1;
        ans[i+2] = l3[s.substr(i, 3)];
      }
    }
  }
  if (prev[m-1] == -2) {
    cout << -1 << '\n';
  }
  else {
    vector<int> v;
    int x = m-1;
    do {
      v.push_back(x);
      x = prev[x];
    } while (x >= 0);
    reverse(all(v));

    cout << sz(v) << '\n';
    for (int j: v) {
      cout << ans[j][0] << ' ' << ans[j][1] << ' ' << ans[j][2] << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
