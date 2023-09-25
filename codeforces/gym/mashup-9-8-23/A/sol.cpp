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

using P = pair<int, int>;
namespace Hash {
  const int M1 = 998244353, M2 = 1e9+9;
  int b = ((rng() % 50) << 1) + 31;

  P append(P h, char c) {
    return {(1LL * h.first * b + (c-'a'+1)) % M1,
            (1LL * h.second * b + (c-'a'+1)) % M2};
  }

  P strhash(const string& s) {
    P h = {0, 0};
    for (char c: s) h = append(h, c);
    return h;
  }
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
// Example : hash pair
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
  size_t operator()(const pair<int, int> x) const {
    size_t h = 0;
    hash_combine(h, x.first);
    hash_combine(h, x.second);
    hash_combine(h, RANDOM);
    return h;
  }
};

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

vector<int> z_function(string s) {
  int n = (int) s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

int count_occ(string s, string t) {
  auto z = z_function(t + '#' + s);
  int ans = 0;
  for (int i = sz(t)+1; i < sz(z); i++) {
    if (z[i] == sz(t)) ans++;
  }
  return ans;
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<pair<int, char>>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<char> parChar;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (auto [j, c]: adj[i]) if (j != p) {
        parChar[j] = c;
        dfs(j, i, t);
      }
    tout[i] = t-1;
  }

  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    tin.resize(sz);
    tout.resize(sz);
    parChar.resize(sz);
  }
  void add_edge(int u, int v, char c) {
    adj[u].emplace_back(v, c);
    adj[v].emplace_back(u, c);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    int t = 0;
    dfs(root, -1, t);
  }

  int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    for (int k = maxk-1; k >= 0; k--) {
      int bb = par[k][b];
      if (bb != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      int bb = par[k][b];
      if (aa != bb) {
        a = aa;
        b = bb;
      }
    }
    return par[0][a];
  }

  bool is_ancestor(int lca, int a) {
    return tin[lca] <= tin[a] && tin[a] <= tout[lca];
  }

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }

  int jump(int u, int d) {
    for (int k = maxk-1; k >= 0; k--) {
      if (d & (1 << k)) u = par[k][u];
    }
    return u;
  }
};

const int maxn = 1e5+5;
int N, Q;
int ans[maxn];

struct Query {
  int id, d, len;
  P s;
};
vector<Query> queries[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;

  Tree tree(N);
  REP(N-1) {
    int u, v; cin >> u >> v; u--, v--;
    char c; cin >> c;
    tree.add_edge(u, v, c);
  }
  tree.init();

  vector<gp_hash_table<P, int, chash>> rel(101);
  cin >> Q;
  F0R(i, Q) {
    int u, v; cin >> u >> v; u--, v--;
    string s; cin >> s;
    string sr = s; reverse(all(sr));
    int lc = tree.lca(u, v);

    P H = Hash::strhash(s), Hr = Hash::strhash(sr);
    rel[sz(s)][H]++;
    rel[sz(s)][Hr]++;
    vector<pair<int, P>> V = {{u, H}, {v, Hr}};
    for (auto [U, S] : V) {
      if (tree.depth[U] - tree.depth[lc] >= sz(s)) {
        queries[U].push_back({i, 1, sz(s), S});
        int uu = tree.jump(U, tree.depth[U] - tree.depth[lc] - sz(s) + 1);
        if (uu > -1) queries[uu].push_back({i, -1, sz(s), S});
      }
    }

    int uu = u;
    if (tree.depth[u] - tree.depth[lc] > sz(s)-1) {
      uu = tree.jump(u, tree.depth[u] - tree.depth[lc] - (sz(s)-1));
    }
    int vv = v;
    if (tree.depth[v] - tree.depth[lc] > sz(s)-1) {
      vv = tree.jump(v, tree.depth[v] - tree.depth[lc] - (sz(s)-1));
    }
    string t;
    while (uu != lc) {
      t += tree.parChar[uu];
      uu = tree.par[0][uu];
    }
    string tr;
    while (vv != lc) {
      tr += tree.parChar[vv];
      vv = tree.par[0][vv];
    }
    reverse(all(tr));
    t += tr;

    ans[i] += count_occ(t, s);
  }

  vector<gp_hash_table<P, int, chash>> cnt(101);
  y_combinator([&](auto dfs, int i, int p) -> void {
    P cur = {0, 0};
    int j = i;
    while (j != 0) {
      cur = Hash::append(cur, tree.parChar[j]);
      int d = tree.depth[i] - tree.depth[j] + 1;
      if (rel[d].find(cur) != rel[d].end()) cnt[d][cur]++;
      if (d >= 100) break;
      j = tree.par[0][j];
    }

    for (const auto& [id, d, len, s]: queries[i]) {
      ans[id] += d * cnt[len][s];
    }
    for (auto [j, c]: tree.adj[i]) {
      if (j == p) continue;
      dfs(j, i);
    }

    cur = {0, 0};
    j = i;
    while (j != 0) {
      cur = Hash::append(cur, tree.parChar[j]);
      int d = tree.depth[i] - tree.depth[j] + 1;
      if (rel[d].find(cur) != rel[d].end()) cnt[d][cur]--;
      if (d >= 100) break;
      j = tree.par[0][j];
    }
  })(0, 0);

  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}
