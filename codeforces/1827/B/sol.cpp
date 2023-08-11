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

struct Sparse
{
  //sparse table data structure for max
  static const int mk = 20;
  int* tb[mk];
  static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
  Sparse(int *a, int n) {
    for (int i = 0; i < mk; i++) {
      tb[i] = new int[n];
    }
    for (int i = 0; i < n; i++) tb[0][i] = a[i];
    for (int k = 1; k <= lg(n); k++) {
      for (int i = 0; i < n; i++) {
        int nx = i + (1<<(k-1));
        if (nx < n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  int getmax(int l, int r) {
    int g = lg(r-l+1);
    return max(tb[g][l],tb[g][r-(1<<g)+1]);
  }

  ~Sparse() {
    F0R(i, mk) delete[] tb[i];
  }
};

const int maxn = 3e5+5;
int A[maxn], B[maxn];

ll solve() {
  int N; cin >> N;
  F0R(i, N) {
    cin >> A[i];
    B[i] = -A[i];
  }

  Sparse mx(A, N);
  Sparse mn(B, N);

  auto leftUp = [&](int i, int x) -> int {
    if (mx.getmax(0, i) <= x) return -1;
    int j = 0;
    F0Rd(k, Sparse::mk-1) {
      int nj = j + (1 << k);
      if (nj <= i && mx.getmax(nj, i) > x) j = nj;
    }
    return j;
  };
  auto leftDown = [&](int i) -> int {
    if (-mn.getmax(0, i) >= A[i]) return -1;
    int j = 0;
    F0Rd(k, Sparse::mk-1) {
      int nj = j + (1 << k);
      if (nj <= i && -mn.getmax(nj, i) < A[i]) j = nj;
    }
    return j;
  };
  auto rightDown = [&](int i) -> int {
    if (-mn.getmax(i, N-1) >= A[i]) return N;
    int j = N-1;
    F0Rd(k, Sparse::mk-1) {
      int nj = j - (1 << k);
      if (nj >= i && -mn.getmax(i, nj) < A[i]) j = nj;
    }
    return j;
  };

  ll ans = 0;
  F0R(i, N) {
    int k = leftDown(i);
    int b = rightDown(i);
    if (k != -1) {
      int a = leftUp(k, A[i]);
      ans += 1LL * (b-i) * (k-a);
    }
  }

  ll sum = 0, cur = 0;
  F0R(i, N) {
    sum += 1LL * i*i - cur;
    cur += i;
  }
  return sum - ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
