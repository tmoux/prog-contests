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

const int maxn = 2e5+5;
int N, M;
vector<int> adj[maxn];

bool vis[maxn];
bool onstack[maxn];
vector<array<int, 3>> ans;

bool dfs(int i, int p) { // return true if parent edge is unpaired
  vis[i] = 1;
  onstack[i] = true;
  vector<int> extras;
  for (int j: adj[i]) {
    if (j == p) continue;
    if (onstack[j]) {
      extras.push_back(j);
    }
    else if (!vis[j]) {
      bool b = dfs(j, i);
      if (b) {
        extras.push_back(j);
      }
    }
  }
  onstack[i] = false;
  while (sz(extras) >= 2) {
    int a = extras.back(); extras.pop_back();
    int b = extras.back(); extras.pop_back();
    ans.push_back({a, i, b});     
  }

  if (extras.empty()) {
    return true;
  }
  else if (i != p) {
    ans.push_back({extras[0], i, p});
    return false;
  }
  else return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  REP(M) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  FOR(i, 1, N+1) {
    if (!vis[i]) {
      dfs(i, i);
    }
  }
  cout << sz(ans) << '\n';
  for (auto [a, b, c]: ans) {
    cout << a << ' ' << b << ' ' << c << '\n';
  }
}
