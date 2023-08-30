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

void solve() {
  int N, M, K; cin >> N >> M >> K;
  vector<int> T(N);
  F0R(i, N) cin >> T[i];


  vector<vector<int>> adj(N);
  vector<int> indegree(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    // add reverse edge
    adj[b].push_back(a);
    indegree[a]++;
  }

  queue<int> q;
  F0R(i, N) if (indegree[i] == 0) q.push(i);

  vector<ll> mxT(N, 0);
  while (!q.empty()) {
    int i = q.front(); q.pop();
    for (int j: adj[i]) {
      int add = T[j] <= T[i] ? T[i]-T[j] : (T[i]+K)-T[j];
      ckmax(mxT[j], mxT[i] + add);
      if (--indegree[j] == 0) q.push(j);
    }
  }

  vector<pair<int, int>> sources;
  F0R(i, N) if (adj[i].empty()) sources.emplace_back(T[i], i);
  sort(all(sources));

  vector<ll> sfx(sz(sources));
  for (int i = sz(sources)-1; i >= 0; i--) {
    int j = sources[i].second;
    sfx[i] = mxT[j] + T[j];
    if (i + 1 < sz(sources)) ckmax(sfx[i], sfx[i+1]);
  }

  ll ans = 1e18;
  ll mxPrefix = 0;
  F0R(i, sz(sources)) {
    int j = sources[i].second;
    ll startTime = sources[i].first;
    ll endTime = sfx[i];
    if (i > 0) ckmax(endTime, mxPrefix + K);
    ckmin(ans, endTime - startTime);

    // update mxPrefix
    ckmax(mxPrefix, mxT[j] + T[j]);
  }
  // vector<int> result(sz(T));
  // std::partial_sum(all(T), result.begin(), [&](int x, int y) {
  //   return max(x, y);
  // });
  // cout << T << endl;
  // cout << result << endl;
  // return;

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
