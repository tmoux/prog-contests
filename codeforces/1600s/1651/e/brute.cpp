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

const int maxn = 1505;
int n;
vector<int> adj[2*maxn];

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  int size(int i) {
    return -par[Find(i)];
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  REP(2*n) {
    int x, y; cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  int ans = 0;
  for (int l = 1; l <= n; l++) {
    for (int r = l; r <= n; r++) {
      for (int L = n+1; L <= 2*n; L++) {
        for (int R = L; R <= 2*n; R++) {
          DSU dsu(2*n);
          FOR(i, l, r+1) {
            for (int j: {0, 1}) {
              if (L <= adj[i][j] && adj[i][j] <= R) {
                dsu.Union(i, adj[i][j]);
              }
            }
          }
          FOR(i, L, R+1) {
            for (int j: {0, 1}) {
              if (l <= adj[i][j] && adj[i][j] <= r) {
                dsu.Union(i, adj[i][j]);
              }
            }
          }

          int cnt = 0;
          FOR(i, l, r+1) if (dsu.Find(i) == i) cnt += dsu.size(i)/2;
          FOR(i, L, R+1) if (dsu.Find(i) == i) cnt += dsu.size(i)/2;
          ans += cnt;
          // cout << l << ' ' << r << ' ' << L << ' ' << R << ": " << cnt << endl;
        }
      }
    }
  }
  cout << ans << '\n';
}
