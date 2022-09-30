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

namespace Seg {
  ll op(ll a, ll b) { return a + b; }

  ll e() { return 0; }
}

ll solve() {
  int N, M; cin >> N >> M;
  using SEG = segtree<ll, Seg::op, Seg::e>;
  vector<SEG> segs(3, SEG(N));
  vector<SEG> segCount(3, SEG(N));

  vector<int> A(N);
  int total = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    segCount[x].set(i, 1);
    segs[x].set(i, i);
    total += x;

    A[i] = x;
  }

  auto first_k_indices_sum = [&](int i, int c, int k) -> ll {
    int r = i;
    for (int K = 20; K >= 0; K--) {
      int nr = r + (1<<K);
      if (nr < N && segCount[c].prod(i, nr) <= k) {
        r = nr;
      }
    }
    if (segCount[c].prod(i, r) == k)
      return segs[c].prod(i, r);
    else return -1;
  };

  auto first_left_k_indices_sum = [&](int i, int c, int k) -> ll {
    int l = i;
    for (int K = 20; K >= 0; K--) {
      int nl = l - (1<<K);
      if (nl >= 0 && segCount[c].prod(nl, i) <= k) {
        l = nl;
      }
    }
    if (segCount[c].prod(l, i) == k)
      return segs[c].prod(l, i);
    else return -1;
  };

  ll ans = 0;
  REP(M) {
    int x, y, z; cin >> x >> y >> z;
    x--;

    total -= A[x];
    segs[A[x]].set(x, 0);
    segCount[A[x]].set(x, 0);
    A[x] = y;
    total += A[x];
    segs[A[x]].set(x, x);
    segCount[A[x]].set(x, 1);

    ll R = 0;
    if (total % 2 == 0) {
      int target = total / 2;

      int lsum = 0;
      for (int i = 1; i <= 2; i++) {
        lsum += segCount[i].prod(0, z-1) * i;
      }

      /*
      DEBUG(target);
      DEBUG(lsum);
      */

      if (lsum < target) {
        int extra = target - lsum;
        ll rs = first_k_indices_sum(z, 2, extra);
        ll ls = first_left_k_indices_sum(z-1, 1, extra);
        if (rs == -1 || ls == -1)
          R = -1;
        else 
          R = rs - ls;
      }
      else if (lsum > target) {
        int extra = lsum - target;
        ll rs = first_k_indices_sum(z, 1, extra);
        ll ls = first_left_k_indices_sum(z-1, 2, extra);
        /*
        F0R(i, N) {
          cout << segs[1].prod(i, i) << ' ';
        }
        cout << '\n';
        DEBUG(extra);
        DEBUG(rs);
        DEBUG(ls);
        */
        if (rs == -1 || ls == -1)
          R = -1;
        else 
          R = rs - ls;
      }
      else {
        R = 0;
      }
    }
    else {
      R = -1;
    }

    // cout << x << ' ' << y << ' ' << z << ": " << R << endl;
    ans += R;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tt, 1, T+1) {
    cout << "Case #" << tt << ": " << solve() << '\n';
  }
}
