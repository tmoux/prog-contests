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

const int maxn = 1<<18;
int N, K, Q;
int A[maxn];
int depth[2*maxn+1];

struct Segment {
  ll prefix, suffix, sum, mss;
  Segment() {}
  Segment(int x) {
    prefix = max(0, x);
    suffix = max(0, x);
    sum = x;
    mss = max(0, x);
  }
};

Segment merge(Segment a, Segment b) {
  Segment ret;
  ret.prefix = max(a.prefix, a.sum + b.prefix);
  ret.suffix = max(b.suffix, b.sum + a.suffix);
  ret.sum = a.sum + b.sum;
  ret.mss = max(a.mss, max(b.mss, a.suffix + b.prefix));
  return ret;
}

map<int, Segment> s[2*maxn+1];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> K;
  N = 1<<K;

  F0R(i, N) {
    cin >> A[i];
    s[i+N][0] = Segment(A[i]);
  }

  for (int i = 1; i < N; i++) {
    depth[i*2] = depth[i] + 1;
    depth[i*2+1] = depth[i] + 1;
  }
  for (int i = N-1; i >= 1; i--) {
    int k = depth[i];
    for (auto [mask, _]: s[i*2]) {
      s[i][mask] = merge(s[i*2][mask], s[i*2+1][mask]);
      s[i][mask^(1<<k)] = merge(s[i*2+1][mask], s[i*2][mask]);
    }
  }

  cin >> Q;
  int mask = 0;
  while (Q--) {
    int k; cin >> k;
    mask ^= (1<<(K-1-k));

    ll ans = s[1][mask].mss;
    cout << ans << '\n';
  }
}
