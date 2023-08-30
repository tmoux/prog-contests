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
  int N, M; cin >> N >> M;
  vector<string> g(N);
  F0R(i, N) {
    cin >> g[i];
  }

  // Check if row/col count is all even: sufficient and necessary
  F0R(i, N) {
    int c = 0;
    F0R(j, M) {
      if (g[i][j] != '.') c ^= 1;
    }
    if (c) {
      cout << -1 << '\n';
      return;
    }
  }
  F0R(j, M) {
    int c = 0;
    F0R(i, N) {
      if (g[i][j] != '.') c ^= 1;
    }
    if (c) {
      cout << -1 << '\n';
      return;
    }
  }

  // Else possible: pair up blocks
  vector<string> ans(N, string(M, '.'));
  F0R(j, M-1) {
    vector<int> v;
    F0R(i, N) {
      if (g[i][j] == 'L' && g[i][j+1] == 'R') {
        v.push_back(i);
      }
    }
    assert(sz(v) % 2 == 0);
    for (int idx = 0; idx < sz(v); idx += 2) {
      ans[v[idx]][j] = 'B';
      ans[v[idx]][j+1] = 'W';
      ans[v[idx+1]][j] = 'W';
      ans[v[idx+1]][j+1] = 'B';
    }
  }
  F0R(i, N-1) {
    vector<int> v;
    F0R(j, M) {
      if (g[i][j] == 'U' && g[i+1][j] == 'D') {
        v.push_back(j);
      }
    }
    assert(sz(v) % 2 == 0);
    // cout << i << ": " << v << endl;
    for (int idx = 0; idx < sz(v); idx += 2) {
      ans[i][v[idx]] = 'B';
      ans[i+1][v[idx]] = 'W';
      ans[i][v[idx+1]] = 'W';
      ans[i+1][v[idx+1]] = 'B';
    }
  }

  F0R(i, N) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
