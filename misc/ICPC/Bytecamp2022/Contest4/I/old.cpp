#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
  template <class Fun>
    class y_combinator_result {
      Fun fun_;

      public:
      template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

      template <class... Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template <class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
!is_same<T_container, string>::value,
  typename T_container::value_type>::type>
  ostream &operator<<(ostream &os, const T_container &v) {
    os << '[';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << ']';
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 2e5+5;
namespace HLD { // {{{
  int preorder[maxn], postorder[maxn], sub_size[maxn], real_to_hld[maxn];
  int pre = 0, hld_id = 1;
  vector<int> adj[maxn];
  struct node {
    int parent, lastPrev, _preorder, _postorder, realid, lastHLD;
  } nodes[maxn];

  int dfs_prep(int i, int par) {
    preorder[i] = pre++;
    sub_size[i] = 1;
    for (int j: adj[i]) {
      if (j == par) continue;
      sub_size[i] += dfs_prep(j,i);
    }
    postorder[i] = pre;
    return sub_size[i];
  }

  void hld(int i, int par, bool newChain = true) {
    real_to_hld[i] = hld_id++;
    int id = real_to_hld[i];
    nodes[id]._preorder = preorder[i];
    nodes[id]._postorder = postorder[i];
    nodes[id].realid = i;
    if (newChain) {
      nodes[id].parent = id;
      nodes[id].lastPrev = real_to_hld[par]; //lastprev[1] = 1
    }
    else {
      nodes[id].parent = nodes[real_to_hld[par]].parent;
      nodes[id].lastPrev = nodes[real_to_hld[par]].lastPrev;
    }
    for (int j: adj[i]) {
      if (j == par) continue;
      if (sub_size[j] * 2 > sub_size[i] - 1) hld(j,i,false);
    }
    for (int j: adj[i]) {
      if (j == par) continue;
      if (sub_size[j] * 2 <= sub_size[i] - 1) hld(j,i,true);
    }
    nodes[id].lastHLD = hld_id-1;
  }

  bool isAncestor(int u, int v) { // whether u is an ancestor of v, hld terms
    return nodes[u]._preorder <= nodes[v]._preorder && nodes[v]._preorder < nodes[u]._postorder;   
  }

  int lca(int u, int v) { // returns lca(u,v) in terms of hld-id's
    while (!isAncestor(nodes[u].parent,v)) {
      u = nodes[u].lastPrev;
    }
    int lo = nodes[u].parent, hi = u;
    if (isAncestor(hi,v)) return hi;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      if (isAncestor(mid,v)) {
        lo = mid;
      }
      else hi = mid;
    }
    return lo;
  }

  vector<pair<int, int>> get_intervals(int i, int lc) { // in hld-id's
    vector<pair<int, int>> ret;  
    while (true) {
      if (nodes[i].parent == nodes[lc].parent) {
        ret.push_back({lc, i});
        break;
      }
      else {
        ret.push_back({nodes[i].parent, i});
        i = nodes[i].lastPrev;
      }
    }
    return ret;
  }
}; // }}}

// persistent segtree {{{
const int MV = 20000000;
int l[MV], r[MV];
int sum[MV];
int nv = 0;
vector<int> roots;
int rp[maxn];
const int SZ = maxn;

int build(int tl, int tr) {
  if (tl == tr) return nv++;
  int tm = (tl + tr) / 2;
  int cv = nv;
  nv++;
  l[cv] = build(tl, tm);
  r[cv] = build(tm+1, tr);
  sum[cv] = sum[l[cv]] + sum[r[cv]];
  return cv;
}

int query(int v, int tl, int tr, int L, int R) {
  if (L > R) return 0;
  if (L == tl && R == tr) return sum[v];
  int tm = (tl+tr)/2;
  return query(l[v], tl, tm, L, min(R, tm)) + query(r[v], tm+1, tr, max(L, tm+1), R);
}

int update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    sum[nv] = new_val + sum[v];
    return nv++;
  }
  int tm = (tl+tr)/2;
  if (pos <= tm) {
    int cv = nv; nv++;
    l[cv] = update(l[v], tl, tm, pos, new_val);
    r[cv] = r[v];
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  } else { 
    int cv = nv; nv++;
    l[cv] = l[v];
    r[cv] = update(r[v], tm+1, tr, pos, new_val);
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  }
} // }}}

int N, Q, P;

vector<int> adj_b[maxn]; // {{{
int tin[maxn], tout[maxn], pt = 0;
const int maxk = 18;
int depth[maxn];
int par[maxk][maxn];

void dfs_b(int i, int p) {
  tin[i] = pt++;
  depth[i] = depth[p] + 1;
  par[0][i] = p;
  for (int k = 1; k < maxk; k++) {
    par[k][i] = par[k-1][par[k-1][i]];
  }
  for (int j: adj_b[i]) if (j != p) {
    dfs_b(j, i);
  }
  tout[i] = pt;
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) swap(a,b);
  for (int k = maxk - 1; k >= 0; k--) {
    int bb = par[k][b];
    if (bb != 0 && depth[bb] >= depth[a])
      b = bb;
  }
  if (a == b) return a;
  for (int k = maxk - 1; k >= 0; k--) {
    int aa = par[k][a];
    int bb = par[k][b];
    if (aa != bb) {
      a = aa;
      b = bb;
    }
  }
  return par[0][a];
} // }}}

int calls = 0;
int sum_leq(int x, int C, int D) {
  calls++;
  int lc = lca(C, D); // LCA of C and D in tree B
  auto sum = [&](int i) -> int {
    return query(roots[rp[x]], 0, SZ-1, 0, tin[i]);
  };
  int res = sum(C) + sum(D) - 2 * sum(lc);
  if (lc <= x) res++;
  return res;
}

int query(int A, int B, int C, int D) {
  int lc = HLD::lca(A, B);
  int clc = sum_leq(lc, C, D) - sum_leq(lc-1, C, D);
  if (A == B) return clc;

  int res = 0;
  for (auto& [l, r]: HLD::get_intervals(A, lc)) {
    // cout << l << ' ' << r << endl;
    res += sum_leq(r, C, D) - sum_leq(l-1, C, D);
  }

  for (auto& [l, r]: HLD::get_intervals(B, lc)) {
    // cout << l << ' ' << r << endl;
    res += sum_leq(r, C, D) - sum_leq(l-1, C, D);
  }
  res -= clc;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q >> P;
  REP(N-1) {
    int u, v; cin >> u >> v;
    HLD::adj[u].push_back(v);
    HLD::adj[v].push_back(u);
  }

  HLD::dfs_prep(1, 1);
  HLD::hld(1, 1, true);

  /*
     for (int i = 1; i <= N; i++) {
     cout << i << ": " << HLD::real_to_hld[i] << endl;
     }
     return 0;
     */

  REP(N-1) {
    int u, v; cin >> u >> v;
    u = HLD::real_to_hld[u];
    v = HLD::real_to_hld[v];
    adj_b[u].push_back(v);
    adj_b[v].push_back(u);
  }
  dfs_b(1, 0);
  roots.push_back(build(0, SZ-1));
  for (int i = 1; i <= N; i++) {
    roots.push_back(update(roots.back(), 0, SZ-1, tin[i], 1));
    roots.push_back(update(roots.back(), 0, SZ-1, tout[i], -1));
    rp[i] = sz(roots)-1;
  }

  int ans = 0;
  REP(Q) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int A = (a + ans * P - 1) % N + 1;
    int B = (b + ans * P - 1) % N + 1;
    int C = (c + ans * P - 1) % N + 1;
    int D = (d + ans * P - 1) % N + 1;

    A = HLD::real_to_hld[A];
    B = HLD::real_to_hld[B];
    C = HLD::real_to_hld[C];
    D = HLD::real_to_hld[D];

    ans = query(A, B, C, D);
    cout << ans << '\n';
  }
}
