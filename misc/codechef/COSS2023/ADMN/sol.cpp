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

const int maxn = 1e5+5;
int N, D;
vector<int> adj[maxn];

int ans = 0;

pair<int, int> dfs(int i, int p) {
  int c = 0;
  vector<int> v;
  for (int j: adj[i]) {
    if (j == p) continue;
    c++;
    auto [x, y] = dfs(j, i);
    x++, y++;
    v.push_back(x);
    v.push_back(y);
  }
  if (c == 0) {
    return {0, 0};
  }
  sort(all(v));
  // cout << i << ": " << v << endl;
  if (v.front() < 0) {
    vector<int> nv;
    int x = -v.front();
    for (auto d: v) {
      if (0 <= d && d < x) continue;
      else nv.push_back(d);
    }
    v = nv;
  }
  int mxd = v.back();
  if (i == 1) {
    if (mxd >= 0) ans++;
    return {0, 0};
  }
  else {
    if (mxd >= D) {
      // DEBUG(i);
      // DEBUG(mxd);
      ans++;
      return {-D-1, -D-1};
    }
    else {
      return {v.back(), v.front()};
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> D;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  if (N == 1) {
    cout << 1 << '\n';
    return 0;
  }
  else if (D == 0) {
    cout << N << '\n';
    return 0;
  }

  dfs(1, 1);
  cout << ans << '\n';
}
