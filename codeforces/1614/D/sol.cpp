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

const int maxx = 2e7+7;

int spf[maxx];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxx; i++) if (!spf[i]) {
      for (int j = i; j < maxx; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

int N, A[maxx];
int cnt[maxx];

ll dp[maxx];

vector<int> primeDivisors(int x) {
  map<int, int> mp;
  while (x > 1) {
    mp[spf[x]]++;
    x /= spf[x];
  }
  vector<int> ps;
  for (auto [p, c]: mp) ps.push_back(p);
  return ps;
}

vector<int> divisors(int x) {
  map<int, int> mp;
    while (x > 1) {
      mp[spf[x]]++;
    x /= spf[x];
  }
  vector<pair<int, int>> v;
  for (auto p: mp) v.push_back(p);

  vector<int> divisors;
  auto rec = y_combinator([&](auto rec, int i, int c) -> void {
    if (i == sz(v)) divisors.push_back(c);
    else {
      int mult = 1;
      for (int j = 0; j <= v[i].second; j++) {
        rec(i+1, mult * c);
        mult *= v[i].first;
      }
    }
  });
  rec(0, 1);
  return divisors;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N;
  F0R(i, N) {
    int x; cin >> x;
    A[x]++;
  }
  for (int i = 1; i < maxx; i++) {
    if (A[i]) {
      auto ds = divisors(i);
      for (auto d: ds) {
        cnt[d] += A[i];
      }
    }
  }

  ll ans = 0;
  for (int i = maxx-1; i >= 1; i--) {
    if (cnt[i]) {
      ckmax(dp[i], 1LL * cnt[i] * i);
      ckmax(ans, dp[i]);
      for (int p: primeDivisors(i)) {
        int d = i / p;
        ckmax(dp[d], 1LL * (cnt[d] - cnt[i]) * d + dp[i]);
      }
    }
  }
  cout << ans << '\n';
}
