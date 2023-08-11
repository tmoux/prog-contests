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

const int maxn = 3e5+5;
int N;
int A[maxn];

ll sum[maxn], cnt[maxn], aux = 0;

vector<int> distinct_primes(int X) {
  vector<int> cur_primes;
  int Y = X;
  for (int i = 2; i*i <= X; i++) {
    if (Y % i == 0) {
      cur_primes.push_back(i);
      while (Y % i == 0) Y /= i;
    }
  }
  if (Y > 1) cur_primes.push_back(Y);
  return cur_primes;
}

vector<pair<int, int>> squarefree_divisors(const vector<int>& cur_primes) {
  int S = sz(cur_primes);
  vector<pair<int, int>> divisors;
  for (int mask = 0; mask < (1<<S); mask++) {
    int p = __builtin_popcount(mask) & 1;
    int k = 1;
    for (int i = 0; i < S; i++) if (mask & (1<<i)) {
      k *= cur_primes[i];
    }
    divisors.push_back({k, p});
  }
  return divisors;
}

ll count_coprime(int X, const vector<pair<int, int>>& squarefree_divisors) {
  ll ans = 0;
  for (auto [k, p]: squarefree_divisors) {
    ll x = sum[k] + aux * cnt[k];
    ans += x * (p == 0 ? 1 : -1);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> A[i];
  sort(A, A+N);

  ll ans = 0;
  F0R(i, N) {
    int X = A[i];
    auto cur_primes = distinct_primes(X);
    auto divisors = squarefree_divisors(cur_primes);
    ans += count_coprime(X, divisors);

    for (auto [d, _]: divisors) {
      sum[d] += -1 - i;
      cnt[d]++;
    }
    aux++;
  }
  cout << ans << '\n';
}
