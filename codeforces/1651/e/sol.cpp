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
bool vis[2*maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  REP(2*n) {
    int x, y; cin >> x >> y;
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  ll ans = 0;
  F0R(i, 2*n) {
    if (!vis[i]) {
      vector<int> cyc = {i, adj[i][0]};
      {
        int j = adj[i][0];
        vis[i] = vis[j] = true;
        while (true) {
          if (!vis[adj[j][0]]) j = adj[j][0];
          else if (!vis[adj[j][1]]) j = adj[j][1];
          else break;
          cyc.push_back(j);
          vis[j] = true;
        }
      }

      int m = sz(cyc);
      // add whole cycle contribution
      {
        int l = n-1, r = 0, L = 2*n-1, R = n;
        for (auto x: cyc) {
          if (0 <= x && x < n) {
            ckmin(l, x);
            ckmax(r, x);
          }
          else {
            ckmin(L, x);
            ckmax(R, x);
          }
        }
        ll tr = 1LL * (m+1)/2 * (l+1) * (n-r) * (L-(n-1)) * (2*n-R);
        ans += tr;
      }

      // add path contributions
      F0R(j, m) {
        int a = cyc[(j-1+m)%m];

        int l = n-1, r = 0, L = 2*n-1, R = n;
        FOR(k, 0, m-1) {
          int y = cyc[(j+k)%m];
          int b = cyc[(j+k+1)%m];
          if (0 <= y && y < n) {
            ckmin(l, y);
            ckmax(r, y);
          }
          else {
            ckmin(L, y);
            ckmax(R, y);
          }

          bool bad = (l <= a && a <= r) || (L <= a && a <= R) ||
                     (l <= b && b <= r) || (L <= b && b <= R);
          if (!bad) {
            ll tr = (k+1)/2; // contribution of path
            {
              int d = -1;
              if (0 <= a && a < l) ckmax(d, a);
              if (0 <= b && b < l) ckmax(d, b);
              tr *= l - d;
            }
            {
              int d = n;
              if (r < a && a <= n-1) ckmin(d, a);
              if (r < b && b <= n-1) ckmin(d, b);
              tr *= d - r;
            }
            {
              int d = n-1;
              if (n <= a && a < L) ckmax(d, a);
              if (n <= b && b < L) ckmax(d, b);
              tr *= L - d;
            }
            {
              int d = 2*n;
              if (R < a && a <= 2*n-1) ckmin(d, a);
              if (R < b && b <= 2*n-1) ckmin(d, b);
              tr *= d - R;
            }
            ans += tr;
          }
        }
      }
    }
  }
  cout << ans << '\n';
}
