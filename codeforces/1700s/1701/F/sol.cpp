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

const int maxn = 2e5+5;
int Q, D;

ll ch2(ll x) {
  return x * (x - 1) / 2;
}

class PointTracker {
  private:
    const int BLK = 200;
    int mxblk;
    vector<int> present, val, block;
    vector<ll> cnt, sum, aux; // block aggregates
    ll total;

    ll countRange(int l, int r) {
      ll res = 0;
      while (l != 0 && block[l] < block[r] && block[l] == block[l-1]) {
        res += present[l];
        l++;
      }
      while (block[l] != block[r]) {
        res += cnt[block[l]];
        l += BLK;
      }
      while (l <= r) {
        res += present[l];
        l++;
      }
      return res;
    }
    ll sumRange(int l, int r) {
      ll res = 0;
      while (l != 0 && block[l] < block[r] && block[l] == block[l-1]) {
        if (present[l]) {
          res += val[l] + aux[block[l]];
        }
        l++;
      }
      while (block[l] != block[r]) {
        res += sum[block[l]] + aux[block[l]] * cnt[block[l]];
        l += BLK;
      }
      while (l <= r) {
        if (present[l]) {
          res += val[l] + aux[block[l]];
        }
        l++;
      }
      return res;
    }
    void addRange(int l, int r, int d) {
      while (l != 0 && block[l] < block[r] && block[l] == block[l-1]) {
        if (present[l]) {
          val[l] += d;
          sum[block[l]] += d;
        }
        l++;
      }
      while (block[l] != block[r]) {
        aux[block[l]] += d;
        l += BLK;
      }
      while (l <= r) {
        if (present[l]) {
          val[l] += d;
          sum[block[l]] += d;
        }
        l++;
      }
    }
  public:
    PointTracker() {
      mxblk = (maxn - 1) / BLK + 1;
      present.resize(maxn, 0);
      block.resize(maxn);
      F0R(i, maxn) block[i] = i / BLK;
      val.resize(maxn, 0);
      cnt.resize(mxblk, 0);
      sum.resize(mxblk, 0);
      aux.resize(mxblk, 0);
      total = 0;
    }
    bool in(int x) {
      return present[x];
    }

    void add(int x) {
      cnt[block[x]]++;
      present[x] = 1;
      int c = countRange(max(0, x-D), x-1);
      val[x] = c - aux[block[x]];
      total += ch2(c);
      sum[block[x]] += c - aux[block[x]];

      total += sumRange(x+1, min(maxn-1, x + D));
      addRange(x+1, min(maxn-1, x + D), 1);
    }
    void remove(int x) {
      cnt[block[x]]--;
      present[x] = 0;
      int c = val[x];
      total -= ch2(c + aux[block[x]]);
      sum[block[x]] -= c;

      addRange(x+1, min(maxn-1, x + D), -1);
      total -= sumRange(x+1, min(maxn-1, x + D));
    }
    ll getTotal() const {
      return total;
    }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> Q >> D;
  PointTracker tracker;
  REP(Q) {
    int x; cin >> x;
    if (!tracker.in(x)) {
      tracker.add(x);
    }
    else tracker.remove(x);
    cout << tracker.getTotal() << '\n';
  }
}
