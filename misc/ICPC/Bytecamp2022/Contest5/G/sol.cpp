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

vector<int> primes(int x) {
  vector<int> ret;
  int cp = x;
  for (int i = 2; i*i <= x; i++) {
    if (cp % i == 0) {
      ret.push_back(i);
      while (cp % i == 0) cp /= i;
    }
  }
  if (cp > 1) ret.push_back(cp);
  return ret;
}
vector<int> get_factors(int x) {
  vector<int> factors = {1};
  for (int i = 2; i*i <= x; i++) {
    if (x % i == 0) {
      factors.push_back(i);
      if (x/i != i) factors.push_back(x/i);
    }
  }
  sort(all(factors));
  return factors;
}

set<int> s;
bool good(int x) {
  if (x % 2 == 1) return false;
  auto ps = primes(x);
  map<int, int> mp;
  for (auto p: ps) {
    while (x % p == 0) {
      mp[p]++;
      x /= p;
    }
  }
  double prod = 1;
  for (auto [p, cnt]: mp) {
    if (p <= 1 + prod) {
      prod *= (pow(p, cnt+1)-1)/(p-1);
    }
    else return false;
  }
  s.insert((int)prod);
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  int cnt = 0;
  map<int, bool> is_good;
  int largest_prime = 0;
  for (int x = 1; x <= N; x++) {
    is_good[x] = good(x);
    if (x % 2 == 0 && is_good[x]) {
      cnt++;
      auto ps = primes(x);
      cout << x << ": " << ps << endl;
      ckmax(largest_prime, ps.back());
      DEBUG(largest_prime);
      assert(largest_prime <= 2*sqrt(x));
      continue;

      
      bool f1 = false;
      int y = x;
      int fac2 = 0; while (y % 2 == 0) {
        y /= 2, fac2++;
        f1 |= is_good[y];
      }
      int z = x;
      bool f2 = false;
      int fac3 = 0; while (z % 3 == 0) {
        z /= 3, fac3++;
        f2 |= is_good[z];
      }
      cout << x << ": " << fac2 << ' ' << fac3 << endl;
      auto f = get_factors(x);
      cout << f << endl;
      bool has = false;
      for (int i = 1; i < sz(f); i++) {
        has |= f[i-1]*2+1 < f[i];
        // assert(f[i-1]*2+1 >= f[i]);
      }
      assert(has);
    }
  }
  cout << '\n';
  DEBUG(cnt);
  double prop = (double)cnt/N;
  cout << fixed << setprecision(10) << prop << endl;

  DEBUG(largest_prime);
  DEBUG(sz(s));
}
