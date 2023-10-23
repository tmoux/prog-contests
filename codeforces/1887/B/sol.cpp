#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

const int maxn = 2e5+5;
int N, T;
map<int, vector<int>> adj[maxn];

set<int> active[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> T;
  FOR(i, 1, T+1) {
    int m; cin >> m;
    REP(m) {
      int u, v; cin >> u >> v;
      adj[u][i].push_back(v);
      adj[v][i].push_back(u);
    }
  }
  int K; cin >> K;
  vector<int> V(K);
  F0R(i, K) cin >> V[i];

  auto add = [&](int i) {
    for (const auto& [t, _]: adj[i]) {
      active[t].insert(i);
    }
  };

  set<int> cur = {1};
  add(1);

  F0R(i, K) {
    int t = V[i];
    vector<int> adds;
    for (auto j: active[t]) {
      assert(adj[j].count(t));
      for (auto k: adj[j][t]) {
        if (!cur.count(k)) {
          cur.insert(k);
          adds.push_back(k);
        }
      }
    }
    active[t].clear();
    for (auto k: adds) add(k);

    if (cur.count(N)) {
      cout << i+1 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
}
