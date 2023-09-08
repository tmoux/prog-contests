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

/*
 * Consider the complement graph. We claim the answer is n - (# of isolated vertices).
 * This is clearly an upper bound. To show this is achievable, for each CC, pick a spanning tree.
 * Remember that an edge (a, b) means that the order between a and b DOESN'T matter.
 * We can decompose each tree into a bunch of star subgraphs greedily using a DFS (special case for the root node).
 * In each star, we can assign the labels l..r in P and l+1..r l in Q.
 * This doesn't affect the relative order outside of this "block".
 */

template<typename T>
void output_vector(const vector<T>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << (next(it) == v.end() ? '\n' : ' ');
  }
}

template<typename T>
void output_vector(const vector<T>& v, int offset) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << (*it + offset) << (next(it) == v.end() ? '\n' : ' ');
  }
}

void solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  vector<set<int>> e(N);
  vector<pair<int, int>> edges;
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    e[a].insert(b);
    e[b].insert(a);
    edges.emplace_back(a, b);
  }
  vector<int> P(N), Q(N);

  set<int> unvisited; F0R(i, N) unvisited.insert(i);
  int c = 0;
  F0R(i, N) {
    if (sz(e[i]) == N-1) {
      P[i] = Q[i] = c;
      c++;
    }
    else if (unvisited.count(i)) {
      unvisited.erase(i);
      queue<int> q; q.push(i);
      while (!q.empty()) {
        int j = q.front(); q.pop();
        vector<int> toerase;
        for (int k: unvisited) {
          if (!e[j].count(k)) {
            adj[j].push_back(k);
            adj[k].push_back(j);
            toerase.push_back(k);
            q.push(k);
          }
        }
        for (auto k: toerase) unvisited.erase(k);
      }
    }
  }

  auto assign = [&](int i, const vector<int>& v) {
    P[i] = c;
    F0R(k, sz(v)) P[v[k]] = c + 1 + k;
    Q[i] = c + sz(v);
    F0R(k, sz(v)) Q[v[k]] = c + k;
    c += sz(v) + 1;
  };
  vector<vector<int>> childs(N);
  vector<bool> vis(N);
  auto dfs = y_combinator([&](auto dfs, int i, int p) -> bool {
    vis[i] = 1;
    int ch = -1;
    for (int j: adj[i]) {
      if (j == p) continue;
      ch = j;
      if (dfs(j, i)) childs[i].push_back(j);
    }
    if (!childs[i].empty()) {
      assign(i, childs[i]);
      return false;
    }
    else if (i == p) {
      assert(ch != -1);
      assert(!childs[ch].empty());
      auto v = childs[ch]; v.push_back(i);
      c -= sz(v);
      assign(ch, v);
      return false;
    }
    else return true;
  });
  F0R(i, N) {
    if (sz(e[i]) == N-1) continue;
    if (!vis[i]) dfs(i, i);
  }

  output_vector(P, +1);
  output_vector(Q, +1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
