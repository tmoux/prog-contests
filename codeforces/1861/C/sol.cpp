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

bool solve() {
  string s; cin >> s;
  int cnt = 0;
  int cur = 0;
  vector<vector<int>> adj(sz(s)+1);
  vector<int> par(sz(s)+1);
  vector<bool> isGood(sz(s)+1), isBad(sz(s)+1);

  int depth = 0;
  for (char c: s) {
    if (c == '+') {
      cnt++;
      adj[cur].push_back(cnt);
      par[cnt] = cur;

      cur = cnt;
      depth++;
    }
    else if (c == '-') {
      cur = par[cur];
      depth--;
    }
    else if (c == '0') {
      if (depth <= 1) return false;
      isBad[cur] = 1;
    }
    else if (c == '1') {
      isGood[cur] = 1;
    }
    else assert(false);
  }
  bool poss = true;
  auto dfs = y_combinator([&](auto dfs, int i) -> bool {
    bool hasCheck = isGood[i];
    for (int j: adj[i]) {
      bool b = dfs(j);
      hasCheck = hasCheck || b;
    }
    // cout << i << ": " << hasCheck << endl;
    if (hasCheck && isBad[i]) {
      poss = false;
    }
    return hasCheck;
  });
  dfs(0);
  return poss;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "YES" : "NO") << '\n';
}
