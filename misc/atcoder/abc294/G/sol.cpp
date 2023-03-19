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

namespace atcoder {
  // @param n 0
  // @return minimum non-negative Symbol’s value as variable is void: x s.t. Symbol’s value as variable is void: n
  int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
  }

  template <class S, S (*op)(S, S), S (*e)()> struct segtree {
    public:
      segtree() : segtree(0) {}
      explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
      explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
          update(i);
        }
      }

      void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
      }

      S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
      }

      S prod(int l, int r) const {
        r++; // make range [l, r] inclusive.
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
          if (l & 1) sml = op(sml, d[l++]);
          if (r & 1) smr = op(d[--r], smr);
          l >>= 1;
          r >>= 1;
        }
        return op(sml, smr);
      }

      S all_prod() const { return d[1]; }

      template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
      }
      template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
          while (l % 2 == 0) l >>= 1;
          if (!f(op(sm, d[l]))) {
            while (l < size) {
              l = (2 * l);
              if (f(op(sm, d[l]))) {
                sm = op(sm, d[l]);
                l++;
              }
            }
            return l - size;
          }
          sm = op(sm, d[l]);
          l++;
        } while ((l & -l) != l);
        return _n;
      }

      template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
      }
      template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
          r--;
          while (r > 1 && (r % 2)) r >>= 1;
          if (!f(op(d[r], sm))) {
            while (r < size) {
              r = (2 * r + 1);
              if (f(op(d[r], sm))) {
                sm = op(d[r], sm);
                r--;
              }
            }
            return r + 1 - size;
          }
          sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
      }

    private:
      int _n, size, log;
      std::vector<S> d;

      void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  };
} // namespace atcoder
using atcoder::segtree;

namespace Seg {
  ll op(ll a, ll b) { return a + b; }

  ll e() { return 0; }
}
using SEG = segtree<ll, Seg::op, Seg::e>;

const int maxn = 2e5+5;
namespace HLD
{
  int preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
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

  void hld(int i, int par, bool newChain) {
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
      if (sub_size[j] * 2 > sub_size[i]) hld(j,i,false);
    }
    for (int j: adj[i]) {
      if (j == par) continue;
      if (sub_size[j] * 2 <= sub_size[i]) hld(j,i,true);
    }
    nodes[id].lastHLD = hld_id-1;
  }

  bool isAncestor(int u, int v) { //whether u is an ancestor of v, hld terms
    return nodes[u]._preorder <= nodes[v]._preorder && nodes[v]._preorder < nodes[u]._postorder;
  }

  int lca(int u, int v) { //returns lca(u,v) in terms of hld-id's
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
};
using namespace HLD;

ll getPfx(int u, int lc, const SEG& seg) {
  ll r = 0;
  while (nodes[u].parent != nodes[lc].parent) {
    r += seg.prod(nodes[u].parent,u);
    u = nodes[u].lastPrev;
  }
  r += seg.prod(lc,u);
  r -= seg.get(lc);
  return r;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;

  vector<vector<pair<int, int>>> g(N+1);
  vector<ll> W(N+1);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    g[a].push_back({b, i+1});
    g[b].push_back({a, i+1});
    adj[a].push_back(b);
    adj[b].push_back(a);

    int w; cin >> w;
    W[i+1] = w;
  }

  dfs_prep(1, 0);
  hld(1, 0, true);

  vector<int> edgeToId(N+1);

  SEG seg(N+1);
  y_combinator([&](auto dfs, int i, int p) -> void {
    for (auto [j, id]: g[i]) {
      if (j == p) continue;
      edgeToId[id] = real_to_hld[j]; // !!
      seg.set(real_to_hld[j], W[id]);
      dfs(j, i);
    }
  })(1, 1);

  int Q; cin >> Q;
  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int i, w; cin >> i >> w;
      int v = edgeToId[i];
      seg.set(v, w);
    }
    else {
      int u, v; cin >> u >> v;
      u = real_to_hld[u];
      v = real_to_hld[v];
      int lc = lca(u, v);
      ll ans = getPfx(u, lc, seg) + getPfx(v, lc, seg);
      cout << ans << '\n';
    }
  }
}
