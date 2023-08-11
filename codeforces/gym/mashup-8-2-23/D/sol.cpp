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
  int N, M; cin >> N >> M;
  vector<int> degree(N);
  vector<vector<pair<int, int>>> adj(N);
  vector<array<int, 2>> E(M);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    if (a > b) swap(a, b);
    E[i] = {a, b};
    degree[a]++, degree[b]++;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }
  vector<int> ans(M); // 0 = a -> b, 1 = b -> a

  auto orient = [&](int a, int b) {
    return a < b ? 0 : 1;
  };

  vector<vector<pair<int, int>>> g(N), odds(N);
  vector<int> used(M, 0);
  F0R(i, N) {
    if (degree[i] % 2 == 0) {
      for (auto [j, id]: adj[i]) {
        (degree[j] % 2 == 0 ? g[i] : odds[i]).emplace_back(j, id);
      }
    }
  }

  auto place_edge = [&](int id, int a, int b) {
    used[id] = 1;
    ans[id] = orient(a, b);
  };

  auto get_degree = [&](int i) {
    int d = 0;
    for (auto [j, id]: g[i]) {
      if (used[id]) continue;
      d ^= 1;
    }
    return d;
  };

  auto find_path = [&](int s) -> pair<vector<int>, vector<int>> {
    vector<int> verts, edges;
    vector<bool> vis(N);
    vector<int> verts_ans, edges_ans;
    auto dfs = y_combinator([&](auto dfs, int i) -> void {
      if (!verts_ans.empty()) return;
      vis[i] = 1;
      verts.push_back(i);
      if (i != s && get_degree(i)) {
        verts_ans = verts;
        edges_ans = edges;
        return;
      }
      for (auto [j, id]: g[i]) {
        if (used[id] || vis[j]) continue;
        edges.push_back(id);
        dfs(j);
        edges.pop_back();
      }
      verts.pop_back();
    });
    dfs(s);

    assert(!verts_ans.empty());
    return {verts_ans, edges_ans};
  };

  auto find_cycle = [&](int s) -> pair<vector<int>, vector<int>> {
    vector<int> onstack(N);
    vector<int> verts, edges;
    vector<bool> vis(N);

    vector<int> verts_ans, edges_ans;

    auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
      if (!verts_ans.empty()) return;
      vis[i] = 1;
      onstack[i] = 1;
      verts.push_back(i);
      for (auto [j, id]: g[i]) {
        if (j == p || used[id]) continue;
        if (onstack[j]) {
          // found cycle
          edges.push_back(id);
          int idx = 0;
          while (verts[idx] != j) idx++;
          verts_ans = vector(verts.begin() + idx, verts.end());
          edges_ans = vector(edges.begin() + idx, edges.end());
          return;
        }
      }
      for (auto [j, id]: g[i]) {
        if (used[id] || vis[j]) continue;
        edges.push_back(id);
        dfs(j, i);
        edges.pop_back();
      }
      verts.pop_back();
      onstack[i] = 0;
    });
    dfs(s, s);

    return {verts_ans, edges_ans};
  };

  while (1) {
    int s = -1;
    F0R(i, N) {
      if (degree[i] % 2 != 0) continue;
      if (get_degree(i)) {
        s = i;
        break;
      }
    }

    if (s == -1) break;
    else {
      auto [verts, edges] = find_path(s);
      assert(sz(verts) > 1);
      assert(!odds[s].empty());
      auto [x, id] = odds[s].back(); odds[s].pop_back();
      place_edge(id, x, s);
      for (int i = 0; i + 1 < sz(verts); i++) {
        int id = edges[i];
        place_edge(id, verts[i], verts[i+1]);
      }
      int t = verts.back();
      assert(!odds[t].empty());
      tie(x, id) = odds[t].back(); odds[t].pop_back();
      place_edge(id, t, x);
    }
  }

  F0R(i, N) {
    if (degree[i] % 2 != 0) continue;
    assert(sz(odds[i]) % 2 == 0);
    while (sz(odds[i]) > 0) {
      auto [j, ji] = odds[i].back(); odds[i].pop_back();
      auto [k, ki] = odds[i].back(); odds[i].pop_back();
      place_edge(ji, j, i);
      place_edge(ki, i, k);
    }
    while (1) {
      auto [verts, edges] = find_cycle(i);
      if (edges.empty()) {
        break;
      }
      else {
        for (int i = 0; i < sz(verts); i++) {
          int a = verts[i], b = verts[(i+1)%sz(verts)];
          int id = edges[i];
          place_edge(id, a, b);
        }
      }
    }
  }

  int mx = 0;
  F0R(i, N) {
    if (degree[i] % 2 == 0) mx++;
  }

  cout << mx << '\n';
  F0R(i, M) {
    auto [a, b] = E[i];
    if (ans[i] == 0) {
      cout << a+1 << ' ' << b+1 << '\n';
    }
    else {
      cout << b+1 << ' ' << a+1 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
