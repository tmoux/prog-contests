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

const int maxn = 1005;
int spf[maxn];
int divisors[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }

  for (int i = 1; i < maxn; i++) {
    map<int, int> mp;
    int x = i;
    while (x > 1) {
      mp[spf[x]]++;
      x /= spf[x];
    }

    int prod = 1;
    for (auto [_, c]: mp) {
      prod *= (c + 1);
    }
    divisors[i] = prod;
  }
}

bool ask(int h, int w, int i1, int j1, int i2, int j2, bool flip) {
   if (flip) {
     swap(h, w);
     swap(i1, j1);
     swap(i2, j2);
   }
  cout << "? " << h << ' ' << w << ' ' << i1+1 << ' ' << j1+1 << ' ' << i2+1 << ' ' << j2+1 << endl;
  int x; cin >> x;
  return x;
}

bool check_even(int n, int m, bool flip) {
  bool t = ask(n, m/2, 0, 0, 0, m/2, flip);
  return t;
}

bool check_odd(int n, int m, int s, int p, bool flip) {
  bool t1 = ask(n, s, 0, 0, 0, s+m/p, flip);
  if (t1) {
    bool t2 = ask(n, s, 0, 0, 0, s, flip);
    return t2;
  }
  else return false;
}

void answer(int x) {
  cout << "! " << x << endl;
}

int solve_1d(int d, int n, int m, bool flip) {
  if (d == m) return d;
  assert(m % d == 0);
  int p = spf[m/d];
  if (p == 2) {
    if (check_even(n, m, flip)) {
      // recurse on left
      return solve_1d(d, n, m/2, flip);
    }
    else {
      while (m/d % p == 0) d *= p;
      return solve_1d(d, n, m, flip);
    }
  }
  else {
    int s = (m/p) * (p / 2);
    if (check_odd(n, m, s, p, flip)) {
      // recurse on left
      return solve_1d(d, n, m/p, flip);
    }
    else {
      while (m/d % p == 0) d *= p;
      return solve_1d(d, n, m, flip);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  int N, M;
  cin >> N >> M;
  int d1 = solve_1d(1, N, M, false);
  int d2 = solve_1d(1, M, N, true);

  int ans = divisors[M / d1] * divisors[N / d2];
  answer(ans);
}
