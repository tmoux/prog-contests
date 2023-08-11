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

// From Atcoder ACL
namespace atcoder { // {{{
  // @param n `0 <= n`
  // @return minimum non-negative `x` s.t. `n <= 2**x`
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
} // namespace atcoder }}}
using atcoder::segtree;

const int INF = 1e9;
namespace Seg {
  int op(int a, int b) { return max(a, b); }

  int e() { return -INF; }
}

const int maxn = 2e5+5;
int N, D;
vector<int> adj[maxn];

int depth[maxn];
int tin[maxn], tout[maxn];
int t = 0;

void dfs(int i, int p) {
  depth[i] = depth[p] + 1;
  tin[i] = t++;
  for (int j: adj[i]) {
    if (j != p) {
      dfs(j, i);
    }
  }
  tout[i] = t-1;
};



int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> D;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 1);
  segtree<int, Seg::op, Seg::e> seg1(N);
  segtree<int, Seg::op, Seg::e> seg2(N);

  int m1; cin >> m1;
  REP(m1) {
    int x; cin >> x;
    seg1.set(tin[x], depth[x]);
  }

  int m2; cin >> m2;
  REP(m2) {
    int x; cin >> x;
    seg2.set(tin[x], depth[x]);
  }

  vector<int> dp1(N+1, 0), dp2(N+1, 0);
  auto f1 = y_combinator([&](auto f1, int i, int p) -> int {
    dp1[i] = 0;
    for (int j: adj[i]) if (j != p) {
      int d1 = seg1.prod(tin[j], tout[j]);
      if (d1 < 0) continue;
      else dp1[i] += f1(j, i) + 2;
    }
    return dp1[i];
  });
  auto f2 = y_combinator([&](auto f2, int i, int p) -> int {
    dp2[i] = 0;
    for (int j: adj[i]) if (j != p) {
      int d2 = seg2.prod(tin[j], tout[j]);
      if (d2 < 0) continue;
      else dp2[i] += f2(j, i) + 2;
    }
    return dp2[i];
  });
  f1(1, 1);
  f2(1, 1);

  /*
  for (int i = 1; i <= N; i++) {
    cout << i << ": " << dp2[i] << endl;
  }
  */

  auto f = y_combinator([&](auto f, int i, int p) -> int {
    int sum = 0;
    int curd = depth[i];
    for (int j: adj[i]) if (j != p) {
      int d1 = seg1.prod(tin[j], tout[j]);
      int d2 = seg2.prod(tin[j], tout[j]);
      if (d1 < 0 && d2 < 0) { // don't go in
        continue;
      }
      else if (d1 - curd <= D && d2 - curd <= D) { // both just dfs from j, optimal
        // cout << "OK " << j << ' ' << i << endl;
        if (d1 > 0) sum += 2 + dp1[j];
        if (d2 > 0) sum += 2 + dp2[j];
      }
      else { // both have to go in
        sum += 4 + f(j, i);
      }
    }

    // cout << i << ": " << sum << endl;
    return sum;
  });

  int ans = f(1, 1);
  cout << ans << '\n';
}
