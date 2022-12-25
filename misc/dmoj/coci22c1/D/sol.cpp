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

const int maxn = 1e7+7;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

int num_divisors(int x) {
  map<int, int> mp;
  while (x > 1) {
    int p = spf[x];
    mp[p]++;
    x /= p;
  }
  int r = 1;
  for (auto [_, c]: mp) r *= c + 1;
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();

  int N; cin >> N;
  F0R(i, N) {
    int x, y; cin >> x >> y;
    if (x == 0 && y == 0) {
      cout << 0 << '\n';
    }
    else if (x == 0 || y == 0) {
      int X = x == 0 ? y : x;
      while (X % 2 == 0) X /= 2;
      cout << num_divisors(X) << '\n';
    }
    else {
      while (x % 2 == 0 && y % 2 == 0) {
        x /= 2, y /= 2;
      }
      if ((x % 2 == 0) == (y % 2 == 0)) {
        cout << 0 << '\n';
      }
      else {
        int gcd = __gcd(x, y);
        cout << num_divisors(gcd) << '\n';
      }
    }
  }
}
