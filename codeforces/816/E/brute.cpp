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

// dp[i][j] = min cost to buy j items, considering the first i
// Given a tree, need to take all the ancestors if using a coupon.
// Don't actually need to use a coupon, can just buy independently.
// If buying independently, then cannot use coupon in the subtree.
// dp[i][j][f]: min cost to buy j items, f = 1 -> used a coupon.

const int maxn = 55, INF = 1e9+9;
int N, B;
vector<int> adj[maxn];
int par[maxn];
int C[maxn], D[maxn];

int ans = 0;
vector<int> v;
void rec() {
  if (sz(v) == N) {
    bool poss = true;
    int cost = 0;
    int cnt = 0;

    FOR(i, 1, N+1) {
      if (v[i-1] == 0) continue;
      else if (v[i-1] == 1) {
        cnt++;
        cost += C[i];
      }
      else if (v[i-1] == 2) {
        cnt++;
        cost += C[i] - D[i];
        if (i > 1 && v[par[i]-1] != 2) {
          poss = false;
          break;
        }
      }
    }
    if (poss && cost <= B) {
      // cout << v << ": " << cnt << endl;
      ckmax(ans, cnt);
    }
    return;
  }

  for (int x = 0; x <= 2; x++) {
    v.push_back(x);
    rec();
    v.pop_back();
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> B;
  FOR(i, 1, N+1) {
    cin >> C[i] >> D[i];
    if (i >= 2) {
      int p; cin >> p;
      par[i] = p;
    }
  }

  rec();
  cout << ans << '\n';
}
