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

int N, M;
void madd(int& a, int b) {
  a += b;
  if (a >= M) a -= M;
}
int msub(int a, int b) {
  madd(a, M-b);
  return a;
}
int mult(int a, int b) {
  return (1LL*a*b) % M;
}
int modexp(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b&1) res = mult(res,a);
    a = mult(a,a);
    b >>= 1;
  }
  return res;
}
int inverse(int x) {
  return modexp(x,M-2);
}

const int maxn = 3e6+6;
int fac[maxn], ifac[maxn], inv[maxn];

int choose(int n, int r) {
  assert(n >= r);
  return mult(fac[n], mult(ifac[r], ifac[n-r]));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  fac[0] = ifac[0] = 1;
  inv[0] = inv[1] = 1;
  for (int i = 2; i < maxn; i++) {
    inv[i] = (M - (1LL * (M/i) * inv[M%i]) % M) % M;
  }
  for (int i = 1; i < maxn; i++) {
    fac[i] = mult(i, fac[i-1]);
    ifac[i] = mult(inv[i], ifac[i-1]);
  }

  int c0 = 1;
  int c1 = msub(mult(2, fac[2*N]), fac[N]);

  int A = mult(fac[2*N], mult(fac[2*N], ifac[N]));
  int O = 0;
  for (int r = 0; r <= N; r++) {
    int add = 0;
    add = choose(r+N, r);
    add = mult(add, choose(N, r));
    add = mult(add, choose(N, r));
    madd(O, add);
  }
  O = mult(O, mult(fac[N], mult(fac[N], fac[N])));

  int c2 = msub(mult(2, A), O);
  int c3 = fac[3*N];

  int ans = 0;
  madd(ans, mult(1, msub(c1, c0)));
  madd(ans, mult(2, msub(c2, c1)));
  madd(ans, mult(3, msub(c3, c2)));
  cout << ans << '\n';
}
