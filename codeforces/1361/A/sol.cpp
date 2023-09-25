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

void imposs() {
  cout << -1 << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> topic(N);
  map<int, vector<int>> which;
  F0R(i, N) {
    cin >> topic[i];
    which[topic[i]].push_back(i);
  }

  vector<int> ans;
  for (const auto& [t, v]: which) {
    for (auto i: v) {
      vector<int> has(t+1);
      for (int j: adj[i]) {
        if (topic[j] == t) {
          imposs();
        }
        else if (topic[j] < t) {
          has[topic[j]] = 1;
        }
      }
      for (int k = 1; k < t; k++) {
        if (!has[k]) imposs();
      }
      ans.push_back(i);
    }
  }

  assert(sz(ans) == N);
  for (auto i: ans) {
    cout << i+1 << ' ';
  }
  cout << '\n';
}
