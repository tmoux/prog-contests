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

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
  int n = sz(a);
  if (n == 1) return;
  vector<cd> a0(n / 2), a1(n / 2);
  for (int i = 0; 2 * i < n; i++) {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }
  fft(a0, invert);
  fft(a1, invert);

  double ang = 2 * PI / n * (invert ? -1 : 1);

  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; i++) {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    if (invert) {
      a[i] /= 2;
      a[i + n / 2] /= 2;
    }
    w *= wn;
  }
}

vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
  vector<cd> fa(all(a)), fb(all(b));
  int n = 1;
  while (n < sz(a) + sz(b)) n *= 2;
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  F0R(i, n) fa[i] *= fb[i];
  fft(fa, true);

  vector<ll> result(n);
  F0R(i, n) {
    result[i] = round(fa[i].real());
  }
  return result;
}

void solve() {
  int n;
  cin >> n;
  n++;
  vector<ll> a(n), b(n);
  F0R(i, n) cin >> a[i];
  F0R(i, n) cin >> b[i];
  reverse(all(a));
  reverse(all(b));
  auto c = multiply(a, b);
  int N = 2 * (n - 1) + 1;
  vector<ll> ans;
  F0R(i, N) {
    ans.push_back(c[i]);
  }
  reverse(all(ans));
  F0R(i, N) {
    cout << ans[i] << " \n"[i == N - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  while (T--) { solve(); }
}
