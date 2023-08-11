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
namespace atcoder { //{{{
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

const int maxn = 1e5+5;
int N;
pair<int,int> pos[maxn][2];

int order(pair<int,int> p) {
  auto [x, y] = p;
  if (x >= y) return y;
  else return y + (y - x);
}

int dist(pair<int,int> a, pair<int,int> b) {
  assert(max(a.first, a.second) == max(b.first, b.second));
  return abs(order(a) - order(b));
}

pair<int,int> Up(pair<int,int> p) {
  return {p.first + 1, p.second};
};
pair<int,int> Right(pair<int,int> p) {
  return {p.first, p.second + 1};
};

namespace Seg {
  struct Node { 
    bool id;
    pair<int,int> p[2][2];
    ll d[2][2];
    Node() {
      id = true;
      p[0][0] = p[1][0] = {-1, -1};
      p[0][1] = p[1][1] = {-1, -1};
    }

    Node(int i) {
      id = false;
      p[0][0] = p[1][0] = pos[i][0];
      p[0][1] = p[1][1] = pos[i][1];
      d[0][0] = d[1][1] = 0;
      d[0][1] = d[1][0] = dist(pos[i][0], pos[i][1]);
    }
  };
  Node op(Node a, Node b) {
    if (a.id) return b;
    if (b.id) return a;
    // assume a and b are contiguous intervals
    Node ret;
    ret.id = false;
    ret.p[0][0] = a.p[0][0];
    ret.p[0][1] = a.p[0][1];
    ret.p[1][0] = b.p[1][0];
    ret.p[1][1] = b.p[1][1];

    int d00 = 1 + dist(   Up(a.p[1][0]), b.p[0][0]);
    int d01 = 1 + dist(   Up(a.p[1][0]), b.p[0][1]);
    int d10 = 1 + dist(Right(a.p[1][1]), b.p[0][0]);
    int d11 = 1 + dist(Right(a.p[1][1]), b.p[0][1]);

    F0R(i, 2) F0R(j, 2) {
      vector<ll> v = {a.d[i][0] + d00 + b.d[0][j],
                      a.d[i][0] + d01 + b.d[1][j],
                      a.d[i][1] + d10 + b.d[0][j],
                      a.d[i][1] + d11 + b.d[1][j]};
      ret.d[i][j] = *min_element(all(v));
    }

    return ret;
  }

  Node e() {
    return Node();
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  vector<Seg::Node> v(N-1);
  F0R(i, N-1) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;
    pos[i][0] = {x1, y1};
    pos[i][1] = {x2, y2};
    v[i] = Seg::Node(i);
  }

  segtree<Seg::Node, Seg::op, Seg::e> seg(v);

  int Q; cin >> Q;
  REP(Q) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;
    int i = max(x1, y1);
    int j = max(x2, y2);
    if (i > j) {
      swap(i, j);
      swap(x1, x2);
      swap(y1, y2);
    }
    pair<int,int> a = {x1, y1};
    pair<int,int> b = {x2, y2};
    if (i == j) {
      cout << dist(a, b) << '\n';
    }
    else {
      j--;
      auto node = seg.prod(i, j);

      ll ans = 1e18;
      F0R(x, 2) {
        ckmin(ans, dist(a, pos[i][x]) + node.d[x][0] + 1 + dist(   Up(node.p[1][0]), b));
        ckmin(ans, dist(a, pos[i][x]) + node.d[x][1] + 1 + dist(Right(node.p[1][1]), b));
      }
      cout << ans << '\n';
    }
  }
}
