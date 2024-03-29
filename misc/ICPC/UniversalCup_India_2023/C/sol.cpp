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
  using T = array<int, 3>;
  T op(T a, T b) { return max(a, b); }

  T e() { return {-1, -1, -1}; }
}

struct IntervalManager {
  int N;
  vector<set<array<int, 3>>> S;
  segtree<Seg::T, Seg::op, Seg::e> seg;
  IntervalManager(int _N) : N(_N) {
    S.resize(N);
    seg = segtree<Seg::T, Seg::op, Seg::e>(N);
  }

  void add(int i, int l, int r) {
    S[l].insert({r, l, i});
  }

  void init() {
    F0R(i, N) {
      if (!S[i].empty()) {
        seg.set(i, *S[i].rbegin());
      }
    }
  }

  int query(int i) {
    auto [r, l, id] = seg.prod(0, i);
    // cout << "query " << i << ": " << seg.prod(0, i) << endl;
    // cout << S << endl;
    if (r < i) return -1;
    else {
      assert(l <= i);
      assert(S[l].count({r, l, id}));
      S[l].erase({r, l, id});
      seg.set(l, S[l].empty() ? Seg::e() : *S[l].rbegin());
      return id;
    }
  }
};

struct TwoSat {
  int N, n;
  vector<vector<int>> adj, adj_t;
  vector<bool> used;
  vector<int> order, comp;
  vector<bool> assignment;

  vector<pair<int, int>> I, IR;
  IntervalManager track, trackR;

  set<int> VIS;

  TwoSat(int _N) : track(_N), trackR(_N) {
    N = _N;
    n = 2 * N;
    adj.resize(n);
    adj_t.resize(n);
    I.resize(N, {1e9, 1e9});
    IR.resize(N, {1e9, 1e9});
  }

  void dfs1(int v) {
    used[v] = true;
    if (VIS.count(v)) VIS.erase(v);
    for (int u : adj[v]) {
      if (!used[u])
        dfs1(u);
    }
    if (v < N) {
      while (true) {
        auto it = VIS.lower_bound(I[v].first);
        if (it != VIS.end() && *it <= I[v].second) {
          int u = *it;
          if (!used[u]) dfs1(u);
        }
        else break;
      }
      while (true) {
        int u = track.query(v);
        if (u != -1) {
          if (!used[u+N]) dfs1(u+N);
        }
        else break;
      }
    }
    order.push_back(v);
  }

  void dfs2(int v, int cl) {
    comp[v] = cl;
    if (VIS.count(v)) VIS.erase(v);
    for (int u : adj_t[v]) {
      if (comp[u] == -1)
        dfs2(u, cl);
    }
    if (v >= N) {
      while (true) {
        auto it = VIS.lower_bound(IR[v-N].first);
        if (it != VIS.end() && *it <= IR[v-N].second) {
          int u = *it;
          if (comp[u] == -1) dfs2(u, cl);
        }
        else break;
      }
      while (true) {
        int u = trackR.query(v-N);
        if (u != -1) {
          if (comp[u] == -1) dfs2(u, cl);
        }
        else break;
      }
    }
  }

  bool solve_2SAT() {
    order.clear();
    used.assign(n, false);

    track.init();
    FOR(i, N, 2*N) VIS.insert(i);
    for (int i = 0; i < n; ++i) {
      if (!used[i])
        dfs1(i);
    }

    trackR.init();
    comp.assign(n, -1);
    VIS.clear();
    F0R(i, N) VIS.insert(i);
    for (int i = 0, j = 0; i < n; ++i) {
      int v = order[n - i - 1];
      if (comp[v] == -1)
        dfs2(v, j++);
    }

    // F0R(i, n) {
    //   cout << i << ": " << comp[i] << endl;
    // }
    // assignment.assign(n / 2, false);
    for (int i = 0; i < N; i++) {
      if (comp[i] == comp[i + N]) {
        // cout << "HUH " << i << ' ' << comp[i] << ' ' << comp[i+N] << endl;
        return false;
      }
      // assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
  }

  void add_disjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated
    a = na ? a + N : a;
    b = nb ? b + N : b;

    int neg_a = na ? a : a + N;
    int neg_b = nb ? b : b + N;

    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    // cout << neg_a << ' ' << b << endl;
    // cout << neg_b << ' ' << a << endl;
    adj_t[b].push_back(neg_a);
    adj_t[a].push_back(neg_b);
  }

  void add_nointersect(int a, int l, int r) {
    // a -> !l, !l+1, ..., !r
    // l, l+1, ..., r -> !a
    I[a] = {l+N, r+N}; // note we should add N to get real indices
    // FOR(i, l, r+1) {
    //   // add_disjunction(a, false, i, false);
    //   // adj[a].push_back(i+N);
    //   // adj[i].push_back(a+N);

    //   adj_t[a+N].push_back(i);
    //   adj_t[i+N].push_back(a);

    //   // cout << a << ' ' << i+N << endl;
    //   // cout << i << ' ' << a+N << endl;
    // }
    track.add(a, l, r);

    // !a -> l, l+1, ..., r
    // !l, !l+1, ..., !r -> a
    IR[a] = {l, r};
    trackR.add(a, l, r); // note +/- switched
  }
};

void solve() {
  int N, M; cin >> N >> M;
  vector<array<int, 3>> vs(N);
  F0R(i, N) {
    cin >> vs[i][0] >> vs[i][1];
    vs[i][2] = i;
  }
  sort(all(vs));
  vector<int> toNewId(N);
  F0R(i, N) {
    toNewId[vs[i][2]] = i;
  }

  TwoSat TS(N);
  F0R(j, M) {
    int a, b; cin >> a >> b;
    a--, b--;
    // add a OR b
    a = toNewId[a];
    b = toNewId[b];
    TS.add_disjunction(a, false, b, false);
  }
  // cout << vs << endl;
  F0R(i, N) {
    array<int, 3> arr = {vs[i][1]+1, -1, -1};
    auto it = lower_bound(all(vs), arr);
    auto r = std::distance(vs.begin(), it) - 1;
    if (r > i) {
      int l = i+1;
      TS.add_nointersect(i, l, r);
      // cout << i << ": " << l << ' ' << r << endl;
    }
  }

  cout << (TS.solve_2SAT() ? "YES" : "NO") << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
