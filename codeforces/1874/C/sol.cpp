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

const int MX = 15;
ll ch[MX][MX];

ll choose(int n, int c) {
  if (n < 0 || c < 0 || n < c) return 0;
  return ch[n][c];
}

double solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
  }

  vector<double> dp(N);
  dp[N-1] = 1;
  for (int i = N-2; i >= 0; i--) {
    int k = sz(adj[i]);
    if (k == 0) dp[i] = 0;
    else {
      vector<double> v;
      for (int j: adj[i]) {
        v.push_back(dp[j]);
        // dp[i] += dp[j];
      }
      vector<bool> taken(k);
      auto select = [&]() -> int {
        vector<int> v;
        F0R(i, k) if (!taken[i]) v.push_back(i);
        assert(!v.empty());
        return v[rng() % sz(v)];
      };
      int B = 1000;
      REP(B) {
        taken.resize(k, 0);
        int num = k;
        while (num > 0) {
          DEBUG(num);
          cout << taken << endl;
          int a = select(), b = select();
          cout << "selected " << a << ' ' << b << endl;
          if (a == b) {
            dp[i] += dp[a] / B;
            break;
          }
          else {
            taken[a] = taken[b] = 1;
            num -= 2;
            DEBUG(num);
          }
        }
      }

      // sort(all(v), greater());
      // vector<double> curdp(k+1);
      // for (int j = k; j >= 0; j--) {
      //   if (2*j >= k) curdp[j] = 0;
      //   else {
      //     curdp[j] = (double)(k - 2 * j - 1) / (k - 2 * j) * curdp[j+1];
      //     double prob = 0;
      //     for (int x = 0; x + 1 + 2 * j <= k; x++) {
      //       ll num = choose(k-2*j-(x+1), j-x);
      //       ll den = choose(k-2*j, j);
      //       if (num == 0 && den == 0) prob += v[j + x];
      //       // cout << x << ": " << num << ' ' << den << endl;
      //       else prob += v[j + x] * ((double)num / den);
      //     }
      //     curdp[j] += (double)(1) / (k - 2 * j) * v[j];
      //     // cout << i+1 << ' ' << j << ": " << curdp[j] << endl;
      //   }
      // }
      // dp[i] = curdp[0];
    }
  }

  return dp[0];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ch[0][0] = 1;
  for (int i = 1; i < MX; i++) {
    ch[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      ch[i][j] = ch[i-1][j-1] + ch[i-1][j];
    }
  }
  int T; cin >> T;
  cout << fixed << setprecision(10);
  while (T--) cout << solve() << '\n';
}
