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

ll solve() {
  int N; cin >> N;
  vector<int> F(N);
  for (auto& x: F) cin >> x;
  vector<vector<int>> rev(N);
  vector<int> adj(N);
  vector<int> deg(N, 0);
  F0R(i, N) {
    int j; cin >> j; j--;
    if (j != -1) {
      rev[j].push_back(i);
      deg[j]++;
    }
    adj[i] = j;
  }
  queue<int> q;
  F0R(i, N) if (rev[i].empty()) q.push(i);

  ll ans = 0;
  while (!q.empty()) {
    int i = q.front(); q.pop();
    vector<array<int, 2>> v;
    if (!rev[i].empty()) {
      for (int j: rev[i]) {
        v.push_back({F[j], j});
      }
      sort(all(v));
      ckmax(F[i], v[0][0]);
      for (int j = 1; j < sz(v); j++) {
        // cout << "adding " << v[j][1] +1 << ' ' << v[j][0] << endl;
        ans += v[j][0];
      }
    }
    // cout << i+1 << ": " << F[i] << endl;
    if (adj[i] != -1 && --deg[adj[i]] == 0) q.push(adj[i]);
  }
  F0R(i, N) if (adj[i] == -1) {
    // cout << "adding " << i+1 << ' ' << F[i] << endl;
    ans += F[i];
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tt, 1, T+1) {
    cout << "Case #" << tt << ": " << solve() << '\n';
  }
}
