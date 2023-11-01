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
  int M; cin >> M;
  vector<vector<int>> adj(N);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto bfs = [&](int i, int t) -> vector<vector<int>> {
    vector<vector<int>> dist(N, vector<int>(2, -1));
    dist[i][t] = 0;
    queue<pair<int, int>> q; q.push({i, t});
    while (!q.empty()) {
      auto [j, t] = q.front(); q.pop();
      for (int k: adj[j]) {
        if (dist[k][t^1] == -1) {
          dist[k][t^1] = dist[j][t] + 1;
          q.push({k, t^1});
        }
      }
    }
    return dist;
  };

  bool even_poss = true;
  int evenAns = 0;
  auto evenDist = bfs(0, 0);
  F0R(i, N) {
    if (evenDist[i][0] == -1) {
      even_poss = false;
      break;
    }
    else {
      ckmax(evenAns, evenDist[i][0]);
    }
  }

  bool odd_poss = true;
  int oddAns = 0;
  F0R(i, N) {
    if (evenDist[i][1] == -1) {
      odd_poss = false;
      break;
    }
    else {
      ckmax(oddAns, evenDist[i][1]);
    }
  }

  int ans = 2e9;
  if (even_poss) ckmin(ans, evenAns);
  if (odd_poss) ckmin(ans, oddAns);
  return ans < 2e9 ? ans : -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
