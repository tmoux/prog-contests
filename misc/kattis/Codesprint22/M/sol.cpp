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

int digits(int x) {
  int r = 0;
  while (x) {
    r++;
    x /= 10;
  }
  return r;
}

ll lcm(ll a, ll b) {
  return a*b/__gcd(a, b);
}

int modexp(int a, int b, int M) {
  int r = 1;
  while (b) {
    if (b&1) r = (1LL * r * a) % M;
    a = (1LL * a * a) % M;
    b >>= 1;
  }
  return r;
}

int e10[11];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  e10[0] = 1;
  for (int i = 1; i < 11; i++) {
    e10[i] = 10 * e10[i-1];
  }

  int N; cin >> N;
  vector<int> A(N);

  set<int> vs;
  int m1 = 1;
  int m2 = 1;
  F0R(i, 30) {
    m2 = 1;
    F0R(j, 10) {
      if (1LL * m1 * m2 + 1 > 1000000000) break;
      vs.insert(m1 * m2 + 1);
      m2 *= 5;
    }
    m1 *= 2;
  }

  F0R(i, N) {
    cin >> A[i];
  }
  shuffle(all(A), rng);

  for (int c: vs) {
    bool flag = true;
    F0R(i, N) {
      int d = digits(A[i]);
      int x = modexp(A[i], c, e10[d]);
      flag &= x == A[i];
      if (!flag) break;
    }
    if (flag) {
      cout << c << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
}
