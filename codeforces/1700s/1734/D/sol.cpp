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
  using T = pair<pair<ll, int>, pair<ll, int>>;
  T op(T a, T b) {
    pair<ll, int> p1;
    if (a.first.first <= b.first.first) p1 = a.first;
    else p1 = b.first;

    pair<ll, int> p2;
    if (b.second.first >= a.second.first) p2 = b.second;
    else p2 = a.second;

    return {p1, p2};
  }

  T e() {
    return {{1e18, -1}, {-1e18, -1}};
  }
}

bool solve() {
  int N; cin >> N;
  int K; cin >> K; K--;
  vector<ll> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  vector<ll> pref(N), suff(N);
  F0R(i, N) {
    pref[i] = A[i] + (i == 0 ? 0 : pref[i-1]);
  }
  F0Rd(i, N) {
    suff[i] = A[i] + (i + 1 == N ? 0 : suff[i+1]);
  }
  segtree<Seg::T, Seg::op, Seg::e> spref(N), ssuff(N);
  F0R(i, N) {
    spref.set(i, {{pref[i], i}, {pref[i], i}});
    ssuff.set(i, {{suff[i], i}, {suff[i], i}});
  }

  auto can_break_left = [&](int i, ll sum) -> bool {
    if (i == 0) return true;
    ll s = suff[0] - suff[i];
    bool p = sum + ssuff.prod(0, i).first.first - suff[i] >= 0;
    return sum + s >= 0 && p;
  };
  auto can_break_right = [&](int i, ll sum) -> bool {
    if (i == N-1) return true;
    ll s = pref[N-1] - pref[i];
    bool p = sum + spref.prod(i, N-1).first.first - pref[i] >= 0;
    return sum + s >= 0 && p;
  };
  const int MX = 18;
  auto go_max_left = [&](int i, ll sum) -> int {
    int l = i;
    F0Rd(k, MX) {
      int nl = l - (1<<k);
      if (nl >= 0) {
        if (sum + ssuff.prod(nl, i).first.first - suff[i] >= 0) {
          l = nl;
        }
      }
    }
    return ssuff.prod(l, i).second.second;
  };
  auto go_max_right = [&](int i, ll sum) -> int {
    int r = i;
    F0Rd(k, MX) {
      int nr = r + (1<<k);
      if (nr < N) {
        if (sum + spref.prod(i, nr).first.first - pref[i] >= 0) {
          r = nr;
        }
      }
    }
    return spref.prod(i, r).second.second;
  };

  int L = K, R = K;
  ll sum = A[K];
  REP(N) {
    // cout << L << ' ' << R << ' ' << sum << endl;
    if (can_break_left(L, sum)) return true;
    else if (can_break_right(R, sum)) return true;
    int nL = go_max_left(L, sum);
    sum += suff[nL] - suff[L];

    int nR = go_max_right(R, sum);
    sum += pref[nR] - pref[R];

    L = nL, R = nR;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "YES" : "NO") << '\n';
  }
}
