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

const int maxn = 1e6+6;
int N, M;
vector<int> adj[maxn];
int deg[maxn];
int parity[maxn], hit[maxn];
int cnt[maxn];

vector<int> change[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> parity[i];
  }
  REP(M) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    deg[b]++;
  }

  FOR(ii, 1, N+1) {
    change[ii].resize(N+1, 0);

    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(ii);
    bool iscycle = false;
    while (!q.empty()) {
      int i = q.front(); q.pop();
      if (vis[i]) {
        iscycle = true;
        break;
      }
      vis[i] = true;
      change[ii][i] ^= 1;
      for (int j: adj[i]) {
        q.push(j);
      }
    }
  }

  queue<int> q;
  FOR(i, 1, N+1) {
    if (deg[i] == 0) {
      q.push(i);
    }
  }

  int ans = 0;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    // cout << i << ": " << parity[i] << endl;
    if ((parity[i]^hit[i])&1) {
      hit[i] ^= 1;
      ans++;
      for (int j: adj[i]) {
        cnt[j]++;
        hit[j] ^= hit[i];
      }
    }
    for (int j: adj[i]) {
      if (--deg[j] == 0) q.push(j);
    }
  }

  FOR(i, 1, N+1) {
    if (deg[i] > 0 && (parity[i] == 1 || cnt[i] > 0)) {
      cout << -1 << '\n';
      return 0;
    }
  }
  cout << ans << '\n';
}
