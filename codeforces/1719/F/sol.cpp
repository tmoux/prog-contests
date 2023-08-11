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

void solve() {
  int N, Q; cin >> N >> Q;
  vector<int> A(N), B(N);
  F0R(i, N) {
    cin >> A[i];
  }

  int X = N;
  vector<int> primes;
  for (int d = 2; d*d <= N; d++) {
    if (X % d == 0) {
      primes.push_back(d);
      while (X % d == 0) X /= d;
    }
  }
  if (X > 1) primes.push_back(X);

  vector<int> divs;
  for (auto p: primes) divs.push_back(N / p);
  vector<vector<int>> sums(N);
  multiset<ll> ms;
  for (auto d: divs) {
    sums[d].resize(d, 0);
  }

  auto update = [&](int i, int x) -> void {
    int delta = x - A[i];
    A[i] = x;
    for (auto d: divs) {
      int s = i % d;
      if (sums[d][s]) {
        auto it = ms.find(1LL * sums[d][s] * d);
        ms.erase(it);
      }
      sums[d][s] += delta;
      ms.insert(1LL * sums[d][s] * d);
    }
  };
  auto best = [&]() -> ll {
    ll ans = *ms.rbegin();
    return ans;
  };
  for (int d: divs) {
    F0R(i, d) {
      for (int j = i; j < N; j += d) {
        sums[d][i] += A[j];
      }
      ms.insert(1LL * sums[d][i] * d);
    }
  }
  cout << best() << '\n';
  while (Q--) {
    int i, x; cin >> i >> x;
    i--;
    update(i, x);
    cout << best() << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
