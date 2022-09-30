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

namespace Max {
  ll op(ll a, ll b) { return max(a, b); }
  ll e() { return -1e18; }
}

void solve(int tc) {
  int N, M; cin >> N >> M;
  vector<pair<int, int>> v(N);
  vector<int> pos;
  map<int, int> posToIndex;
  F0R(i, N) {
    cin >> v[i].first >> v[i].second;
    pos.push_back(v[i].first);
  }
  sort(all(pos));
  pos.erase(unique(all(pos)), pos.end());
  F0R(i, sz(pos)) posToIndex[pos[i]] = i;

  vector<pair<int, int>> deltas;
  vector<array<int, 3>> Ls, Rs;
  F0R(i, N) {
    auto [x, p] = v[i];
    deltas.push_back({x-p, 1});
    deltas.push_back({x, -2});
    deltas.push_back({x+p, 1});

    Ls.push_back({x-p, x, i});
    Rs.push_back({x, x+p, i});
  }

  // calculate initial heights {{{
  sort(all(deltas));
  vector<ll> height(N);
  ll delta = 0;
  ll cur_sum = 0;
  int prev_x = deltas[0].first;
  for (auto [x, d]: deltas) {
    cur_sum += delta * (x - prev_x);
    prev_x = x;
    if (posToIndex.count(x)) {
      height[posToIndex[x]] = cur_sum;
    }
    delta += d;
  }
  // }}}

  // prefixes/suffixes {{{
  vector<ll> prefix_max(sz(pos)), suffix_max(sz(pos));
  F0R(i, sz(pos)) {
    prefix_max[i] = height[i];
    if (i > 0) ckmax(prefix_max[i], prefix_max[i-1]); 
  }
  F0Rd(i, sz(pos)) {
    suffix_max[i] = height[i];
    if (i+1 < sz(pos)) ckmax(suffix_max[i], suffix_max[i+1]);
  }
  vector<ll> max_height(N);
  F0R(i, N) {
    auto [x, p] = v[i];
    int d = distance(pos.begin(), lower_bound(all(pos), x-p));
    if (d > 0) ckmax(max_height[i], prefix_max[d-1]);

    d = distance(pos.begin(), upper_bound(all(pos), x+p));
    if (d < sz(pos)) ckmax(max_height[i], suffix_max[d]);
  } // }}}

  // Rs {{{
  segtree<ll, Max::op, Max::e> segr(sz(pos));
  int last_pos = pos.back();
  F0R(i, sz(pos)) {
    segr.set(i, height[i] - (last_pos - pos[i]));
  }

  for (auto [l, r, i]: Rs) {
    int L = distance(pos.begin(), lower_bound(all(pos), l));
    int R = distance(pos.begin(), prev(upper_bound(all(pos), r)));
    if (l <= pos[L] && pos[L] <= pos[R] && pos[R] <= r) {
      ll mx = segr.prod(L, R) + (last_pos - r);
      ckmax(max_height[i], mx);
    }
  } // }}}

  // Ls {{{
  segtree<ll, Max::op, Max::e> segl(sz(pos));
  int init_pos = pos[0];
  F0R(i, sz(pos)) {
    segl.set(i, height[i] - (pos[i] - init_pos));
  }
  for (auto [l, r, i]: Ls) {
    int L = distance(pos.begin(), lower_bound(all(pos), l));
    int R = distance(pos.begin(), prev(upper_bound(all(pos), r)));
    if (l <= pos[L] && pos[L] <= pos[R] && pos[R] <= r) {
      ll mx = segl.prod(L, R) + (l - init_pos);
      ckmax(max_height[i], mx);
    }
  } // }}}

  F0R(i, N) {
    cout << (max_height[i] <= M ? 1 : 0);
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int i = 1; i <= T; i++) {
    solve(i);
  }
}
