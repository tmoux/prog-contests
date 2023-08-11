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

const int maxx = 5e6+6;
vector<int> totient;
vector<int> paths[maxx];
vector<int> phi_from_1_to_n(int n) {
  vector<int>phi(n + 1, 1), sieve(n + 1, -1);

  for(int i = 2; i <= n; i++) {
    if(sieve[i] == -1) {
      sieve[i] = i;
      for(long long j = 1ll * i * i; j <= n; j += i)
        sieve[j] = i;
    }
  }

  for(int i = 2; i <= n; i++) {
    int p = sieve[i], j = i;
    while(j % p == 0) {
      phi[i] *= p;
      j /= p;
    }
    //j is now equal to i / p^k
    phi[i] = (phi[i] / p) * (p - 1) * phi[j];
  }
  return phi;
}

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
  T op(T a, T b) {
    if (a[0] == -1) return b;
    else if (b[0] == -1) return a;
    else {
      int x = a[0], y = b[0];
      int cost = a[2] + b[2];
      for (int i = sz(paths[x])-1, j = sz(paths[y])-1; i >= 0 && j >= 0;) {
        if (paths[x][i] == paths[y][j]) {
          return {paths[x][i], a[1] + b[1], cost};
        }
        else if (paths[x][i] > paths[y][j]) {
          i--;
          cost += a[1];
        }
        else {
          j--;
          cost += b[1];
        }
      }
      assert(false);
    }
  }

  T e() {
    return {-1, -1, -1};
  }

  T init(int x) {
    return {x, 1, 0};
  }
}

const int maxn = 1e5+5;
int N, M;

void getPath(int x) {
  if (!paths[x].empty()) return;
  if (x == 1) {
    paths[x].push_back(1);
  }
  else {
    getPath(totient[x]);
    paths[x] = paths[totient[x]];
    paths[x].push_back(x);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  totient = phi_from_1_to_n(maxx);
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    getPath(A[i]);
  }
  segtree<Seg::T, Seg::op, Seg::e> seg(N);
  F0R(i, N) {
    seg.set(i, Seg::init(A[i]));
  }
  // cout << seg.all_prod() << endl;
  // return 0;

  set<int> indices;
  F0R(i, N) if (A[i] > 1) indices.insert(i);
  while (M--) {
    int t, l, r; cin >> t >> l >> r;
    l--, r--;
    if (t == 1) {
      for (auto it = indices.lower_bound(l); it != indices.end() && *it <= r;) {
        int i = *it;
        A[i] = totient[A[i]];
        seg.set(i, Seg::init(A[i]));
        if (A[i] == 1) {
          indices.erase(it++);
        }
        else ++it;
      }
    }
    else {
      int ans = seg.prod(l, r)[2];
      cout << ans << '\n';
    }
  }
}
