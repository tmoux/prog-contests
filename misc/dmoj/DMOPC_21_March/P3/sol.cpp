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
vector<int> adj[maxn], rev[maxn];
int deg[maxn];
int parity[maxn], hit[maxn];
int cnt[maxn];

bool bad_mark[maxn];

bool check_cycles() {
  FOR(i, 1, N+1) deg[i] = sz(rev[i]);
  queue<int> q;
  FOR(i, 1, N+1) {
    if (deg[i] == 0) {
      q.push(i);
    }
  }
  vector<bool> incycle(N+1, true);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    incycle[i] = false;
    for (int j: adj[i]) if (--deg[j] == 0) {
      q.push(j);
    }
  }

  assert(q.empty());
  bool ret = false;
  FOR(i, 1, N+1) {
    if (incycle[i]) {
      q.push(i);
    }
  }
  vector<bool> vis(N+1, false);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    if (!vis[i]) {
      if (parity[i] == 1) ret = true;
      vis[i] = true;
      bad_mark[i] = true;
      for (int j: rev[i]) q.push(j);
    }
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> parity[i];
  }
  REP(M) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    rev[b].push_back(a);
  }

  if (check_cycles()) {
    cout << -1 << '\n';
    return 0;
  }

  FOR(i, 1, N+1) deg[i] = 0;
  FOR(i, 1, N+1) {
    for (int j: adj[i]) {
      if (!bad_mark[i] && !bad_mark[j]) {
        deg[j]++;
      }
    }
  }
  queue<int> q;
  FOR(i, 1, N+1) {
    if (!bad_mark[i] && deg[i] == 0) {
      q.push(i);
    }
  }

  int ans = 0;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    if (parity[i]^hit[i]) {
      hit[i] ^= 1;
      ans++;
    }
    for (int j: adj[i]) {
      if (bad_mark[j]) continue;
      hit[j] ^= hit[i];
      if (--deg[j] == 0) q.push(j);
    }
  }

  cout << ans << '\n';
}
