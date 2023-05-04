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

int solve() {
  int N, K; cin >> N >> K;
  vector<array<ll, 2>> V(N);
  vector<pair<ll, int>> vec;
  vector<int> toIdx(N);
  F0R(i, N) {
    cin >> V[i][0];
  }
  F0R(i, N) {
    cin >> V[i][1];
  }
  ll sum = 0;
  F0R(i, N) {
    sum += V[i][1] - V[i][0] + 1;
  }
  if (sum < K) {
    return -1;
  }

  ll ans = LLONG_MAX;

  F0R(i, N) {
    vec.push_back({V[i][1] - V[i][0] + 1, i});
  }
  sort(all(vec), greater());
  F0R(i, N) {
    toIdx[vec[i].second] = i;
  }

  segtree<ll, Seg::op, Seg::e> sumS(N), cntS(N);

  auto getcnt = [&](int k) -> pair<ll, ll> {
    // if (sumS.all_prod() < k) return {sumS.all_prod(), cntS.all_prod()};
    int lo = -1, hi = N-1;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      if (sumS.prod(0, mid) >= k) {
        hi = mid;
      }
      else lo = mid;
    }
    return {cntS.prod(0, hi), sumS.prod(0, hi)};
  };

  ll total = 0;
  int ones = 0;
  F0R(i, N) {
    ll cur = V[i][1] - V[i][0] + 1;
    total += cur;
    if (total >= K) {
      if (K == 1) {
        ckmin(ans, V[i][0] + 2);
      }
      else {
        auto tryw = [&](int k) {
          auto [c, s] = getcnt(K - k);
          ll tr = (V[i][0] + k - 1) + 2 * (c + 1);
          ll left = K - k - s;
          if (left > 0) {
            ll t = min(left, cur - k);
            tr += t;
            left -= t;
          }
          if (left > 0) {
            assert(ones >= left);
            tr += 2 * left;
          }
          ckmin(ans, tr);
        };

        for (int k = 1; k <= 1; k++) {
          if (cur >= k) tryw(k);
        }
      }
    }

    if (cur > 1) {
      int idx = toIdx[i];
      sumS.set(idx, cur);
      cntS.set(idx, 1);
    }
    else ones++;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
