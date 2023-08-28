#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
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
  int op(int a, int b) { return a + b; }
  int e() { return 0; }
}

struct Tracker {
  int MX;
  set<pair<int, int>> ms;
  segtree<int, Seg::op, Seg::e> seg, cnt;
  Tracker(int mx) : MX(mx), seg(mx), cnt(mx) {
  }

  void insert(pair<int, int> p) {
    auto [i, id] = p;
    seg.set(i, seg.get(i) + i);
    cnt.set(i, cnt.get(i) + 1);
    ms.insert({i, id});
  }

  void remove(pair<int, int> p) {
    auto [i, id] = p;
    seg.set(i, seg.get(i) - i);
    cnt.set(i, cnt.get(i) - 1);
    ms.erase(ms.find({i, id}));
  }

  int smallestK(int k) { // -1 if invalid, else sum of smallest k elements
    if (cnt.all_prod() < k) return -1;
    int lo = 0, hi = MX;
    while (lo + 1 < hi) {
      int mid = std::midpoint(lo, hi);
      if (cnt.prod(0, mid) < k) lo = mid;
      else hi = mid;
    }
    assert(cnt.prod(0, lo+1) >= k);
    return seg.prod(0, lo) + (k - cnt.prod(0, lo)) * (lo+1);
  }

  vector<int> getSmallestK(int k) {
    assert(sz(ms) >= k);
    vector<int> ids;
    for (auto [x, id]: ms) {
      if (sz(ids) < k) ids.push_back(id);
      else break;
    }
    return ids;
  }
};

const int maxt = 1e4+4;
int N, M, K;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> K;
  array<vector<pair<int, int>>, 4> A;
  F0R(i, N) {
    int t, a, b; cin >> t >> a >> b;
    A[a * 2 + b].emplace_back(t, i+1);
  }
  F0R(i, 4) sort(all(A[i]));
  array<vector<int>, 4> pfx;
  F0R(i, 4) {
    pfx[i].resize(sz(A[i]));
    for (int j = 0; j < sz(A[i]); j++)
      pfx[i][j] = (j > 0 ? pfx[i][j-1] : 0) + A[i][j].first;
  }
  auto getpfx = [&](int i, int j) -> int {
    return j-1 < 0 ? 0 : pfx[i][j-1];
  };

  // F0R(i, 4) {
  //   cout << i << ": " << pfx[i] << endl;
  // }

  const int INF = 2e9 + 9;
  int ans = INF;

  {
    Tracker tracker(maxt);
    for (auto x: A[0]) tracker.insert(x);
    for (auto x: A[3]) tracker.insert(x);

    int p01 = sz(A[1])-1, p10 = sz(A[2])-1;
    for (int x = 0; x <= min(K, sz(A[3])); x++) {
      if (!(K-x > sz(A[1]) || K-x > sz(A[2]))) {
        int need = M - (x + (K - x) + (K - x));
        if (need >= 0) {
          if (need < 0) continue;
          while (p01 >= K-x) {
            tracker.insert(A[1][p01--]);
          }
          while (p10 >= K-x) {
            tracker.insert(A[2][p10--]);
          }

          int tr = getpfx(3, x) +
            getpfx(1, K-x) +
            getpfx(2, K-x) +
            tracker.smallestK(need);
          // cout << x << ": " << tr << endl;
          // DEBUG(getpfx(3, x));
          // DEBUG(getpfx(1, K-x));
          // DEBUG(getpfx(2, K-x));
          // DEBUG(tracker.smallestK(need));
          if (tr != -1) ckmin(ans, tr);
        }
      }

      if (x < sz(A[3])) tracker.remove(A[3][x]);
    }
  }

  if (ans < INF) {
    vector<int> ret;

    {
      Tracker tracker(maxt);
      for (auto x: A[0]) tracker.insert(x);
      for (auto x: A[3]) tracker.insert(x);

      int p01 = sz(A[1])-1, p10 = sz(A[2])-1;
      for (int x = 0; x <= min(K, sz(A[3])); x++) {
        if (!(K-x > sz(A[1]) || K-x > sz(A[2]))) {
          int need = M - (x + (K - x) + (K - x));
          if (need >= 0) {
            while (p01 >= K-x) {
              tracker.insert(A[1][p01--]);
            }
            while (p10 >= K-x) {
              tracker.insert(A[2][p10--]);
            }

            int tr = getpfx(3, x) +
              getpfx(1, K-x) +
              getpfx(2, K-x) +
              tracker.smallestK(need);
            if (tr == ans) {
              ret = tracker.getSmallestK(need);
              F0R(i, x) ret.push_back(A[3][i].second);
              F0R(i, K-x) ret.push_back(A[1][i].second);
              F0R(i, K-x) ret.push_back(A[2][i].second);
              break;
            }
          }
        }

        if (x < sz(A[3])) tracker.remove(A[3][x]);
      }
    }

    cout << ans << '\n';
    for (auto id: ret) cout << id << ' ';
    cout << '\n';
  }
  else cout << -1 << '\n';
}
