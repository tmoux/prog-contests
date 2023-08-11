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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  auto is_odd_comb = [](int n, int k) -> bool { return (k & (n - k)) == 0; };
  int n, k;
  cin >> n >> k;
  vector<vector<bool>> cnt(n + 1);
  for (int i = n; i >= max(0, n - 22); i--) {
    cnt[i] = vector<bool>(i + 1, false);
    for (int j = i; j >= 0; j--) {
      if (j == i)
        cnt[i][j] = is_odd_comb(i, j);
      else
        cnt[i][j] = is_odd_comb(i, j) ^ cnt[i][j + 1];
    }
  }

  vector<int> B(n);
  for (auto &x : B) cin >> x;

  vector<int> ans(1 << 20, 0);
  F0R(l, n) {
    ll x = B[l];
    for (int r = l; r - l + 1 <= 20 && r < n; r++) {
      int nn = (n - 1) - (r - l);
      int kk = k;
      if (l != 0) {
        nn--;
        kk--;
      }
      if (r != n - 1) {
        nn--;
        kk--;
      }

      if (r > l) {
        if (B[r] >= 20) {
          break;
        } else {
          x = x * (1LL << B[r]);
          if (x >= (1 << 20))
            break;
        }
      }

      if (nn < 0 || kk > nn)
        continue;
      bool incl = cnt[nn][max(0, kk)];
      if (incl && x < (1 << 20))
        ans[x] ^= 1;
    }
  }

  if (all_of(all(ans), [](int x) { return x == 0; })) {
    cout << 0 << '\n';
  } else {
    bool start = false;
    F0Rd(i, 1 << 20) {
      if (start)
        cout << ans[i];
      else if (ans[i]) {
        cout << ans[i];
        start = true;
      }
    }
    cout << '\n';
  }
}

