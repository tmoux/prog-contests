#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using ll = long long;
using namespace __gnu_pbds;

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

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
// gp_hash_table<int, array<int, 2>, chash> table;

const int maxn = 2e5+5;
int N, A[maxn];

vector<int> adj[maxn];
int color[maxn];

void dfs(int i, int c, bool& poss) {
  color[i] = c;
  for (int j: adj[i]) {
    if (color[j] == -1) {
      dfs(j, 1 ^ c, poss);
    }
    else if (color[j] == color[i]) {
      poss = false;
    }
  }
}

bool check_bipartite() {
  F0R(i, N) color[i] = -1;
  bool poss = true;
  F0R(i, N) {
    if (color[i] == -1) {
      dfs(i, 0, poss);
    }
  }
  return poss;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
  }
  if (N == 2) {
    cout << "10\n";
    return 0;
  }

  for (int k = 30-1; k >= 0; k--) {
    map<int, vector<int>> mp;
    bool poss = true;
    F0R(i, N) {
      mp[A[i] >> k].push_back(i);
      if (sz(mp[A[i] >> k]) > 2) poss = false;
    }
    if (!poss) continue;
    for (auto [_, vec]: mp) {
      if (sz(vec) == 2) {
        int i = vec[0], j = vec[1];
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
    if (check_bipartite()) {
      F0R(i, N) {
        A[i] &= ~(1 << k);
      }
    }
    else {
      for (auto [_, vec]: mp) {
        if (sz(vec) == 2) {
          int i = vec[0], j = vec[1];
          adj[i].pop_back();
          adj[j].pop_back();
        }
      }
    }
  }

  assert(check_bipartite());
  F0R(i, N) {
    cout << color[i];
  }
  cout << '\n';
}
