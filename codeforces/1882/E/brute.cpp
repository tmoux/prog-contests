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

vector<int> op(const vector<int>& v, int i) {
  vector<int> r;
  for (int j = i+1; j < sz(v); j++) r.push_back(v[j]);
  r.push_back(v[i]);
  for (int j = 0; j < i; j++) r.push_back(v[j]);
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  using vi = vector<int>;
  int n; cin >> n;

  map<vi, vector<vi>> adj;
  vector<int> p(n); iota(all(p), 1);
  do {
    for (int i = 0; i < n; i++) {
      auto v = op(p, i);
      adj[p].push_back(v);
    }
  } while (next_permutation(all(p)));

  for (auto [v, vv]: adj) {
    // cout << v << ": ";
    for (auto u: vv) {
      for (auto i: v) cout << i;
      cout << ' ';
      for (auto i: u) cout << i;
      cout << endl;
    }
    cout << endl;
  }

  map<vi, int> color;
  bool is_bipartite = true;
  auto dfs = y_combinator([&](auto dfs, vi i, int c) -> void {
    color[i] = c;
    for (auto j: adj[i]) {
      if (!color.count(j)) dfs(j, c^1);
      else if (color[j] == c) {
        is_bipartite = false;
      }
    }
  });
  for (auto [v, _]: adj) {
    if (!color.count(v)) dfs(v, 0);
  }
  DEBUG(is_bipartite);
}
