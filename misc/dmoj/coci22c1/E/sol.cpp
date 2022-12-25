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

inline int gcd(int a, int b) {
  return __gcd(a, b);
}

struct Sparse
{
  //sparse table data structure for max
  static const int mk = 20; //change this number based on bounds
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
        if (nx < n) tb[k][i] = gcd(tb[k-1][i],tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  int getgcd(int l, int r) {
    int g = lg(r-l+1);
    return gcd(tb[g][l],tb[g][r-(1<<g)+1]);
  }
};

int N, K;
const int maxn = 1e6+6;
int A[maxn];
ll pre[maxn];

inline ll getsum(int l, int r) {
  return pre[r] - (l == 0 ? 0 : pre[l-1]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N) {
    cin >> A[i];
    pre[i] = A[i];
    if (i > 0) pre[i] += pre[i-1];
  }
  Sparse table(A, N);

  ll ans = 0;

  for (int i = 0; i + K <= N; i++) {
    int G = table.getgcd(i, i+K-1);
    int cur = i+K-1;
    while (true) {
      int lo = cur, hi = N;
      while (lo + 1 < hi) {
        int mid = (lo + hi)/2;
        if (table.getgcd(i, mid) == G) {
          lo = mid;
        }
        else hi = mid;
      }
      ckmax(ans, 1LL * G * getsum(i, lo));
      if (lo == N-1) break;
      else {
        G = table.getgcd(i, lo + 1);
        cur = lo + 1;
      }
    }
  }
  cout << ans << '\n';
}
