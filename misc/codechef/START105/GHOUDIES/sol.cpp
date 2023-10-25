#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

int solve() {
  int N; cin >> N;
  vector<vector<pair<int, char>>> adj(N);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    char c; cin >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }
  string S; cin >> S;
  string T = S; reverse(all(T));

  vector<vector<int>> nS(sz(S)+1, vector<int>(26, sz(S)));
  for (int i = sz(S)-1; i >= 0; i--) {
    for (char c = 'a'; c <= 'z'; c++) {
      if (S[i] == c) nS[i][c-'a'] = i;
      else nS[i][c-'a'] = nS[i+1][c-'a'];
    }
  }
  vector<vector<int>> nT(sz(T)+1, vector<int>(26, sz(S)));
  for (int i = sz(T)-1; i >= 0; i--) {
    for (char c = 'a'; c <= 'z'; c++) {
      if (T[i] == c) nT[i][c-'a'] = i;
      else nT[i][c-'a'] = nT[i+1][c-'a'];
    }
  }

  int ans = 0;
  using vi = vector<int>;
  auto dfs = y_combinator([&](auto dfs, int i, int p) -> pair<vi, vi> {
      vector<int> dpS(sz(S), 0);
      vector<int> dpT(sz(T), 0);
      for (auto [j, c]: adj[i]) {
        if (j == p) continue;
        auto [jS, jT] = dfs(j, i);
        for (int k = sz(S)-1; k >= -1; k--) {
          int l = nS[k+1][c-'a'];
          if (l < sz(S)) ckmax(jS[l], (k >= 0 ? jS[k] : 0) + 1);

          l = nT[k+1][c-'a'];
          if (l < sz(T)) ckmax(jT[l], (k >= 0 ? jT[k] : 0) + 1);
        }
        for (int k = 1; k < sz(T); k++) {
          ckmax(jS[k], jS[k-1]);
          ckmax(jT[k], jT[k-1]);
        }

        ckmax(ans, jS.back());
        ckmax(ans, jT.back());
        // cout << "HUH " << i << ' ' << j << ":\n";
        // DEBUG(dpS);
        // DEBUG(jT);
        for (int k = sz(T); k >= 0; k--) {
          int l = sz(T) - 2 - k;
          ckmax(ans, (k < sz(jT) ? jT[k] : 0) + (l < 0 ? 0 : dpS[l]));
          // cout << "checking " << i+1 << ' ' << j+1 << ' ' << k << ' ' << l << ": " << (k < sz(T) ? jT[k] : 0) + (l < 0 ? 0 : dpS[l]) << endl;
        }

        F0R(k, sz(T)) {
          ckmax(dpS[k], jS[k]);
          ckmax(dpT[k], jT[k]);
        }
      }
      // cout << i+1 << ": " << dpS << ' ' << dpT << endl;
      return {dpS, dpT};
  });
  dfs(0, 0);
  F0R(i, N) reverse(all(adj[i]));
  dfs(0, 0);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
