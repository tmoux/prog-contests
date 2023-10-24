#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

namespace Mobius {
  const int maxn = 1e6+5;
  int mu[maxn];

  void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i < maxn; i++) {
      for (int j = 2*i; j < maxn; j += i) {
        mu[j] -= mu[i];
      }
    }
  }
}
using namespace Mobius;

ll solve() {
  int N; cin >> N;
  vector<int> A(N), has(N+1), cnt(N+1);
  F0R(i, N) {
    cin >> A[i];
    cnt[A[i]]++;
    has[A[i]] = 1;
  }
  FOR(i, 1, N+1) {
    if (has[i]) {
      for (int j = i; j <= N; j += i) {
        has[j] = 1;
      }
    }
  }
  vector<ll> D(N+1); // how many are divisible by d
  for (int d = 1; d <= N; d++) {
    for (int i = d; i <= N; i += d) {
      D[d] += cnt[i];
    }
  }

  auto countPairs = [&](int g) -> ll {
    ll s = 0;
    for (int d = 1; d*g <= N; d++) {
      s += 1LL * mu[d] * D[g*d] * D[g*d];
    }
    return (s - cnt[g]) / 2;
  };

  ll total = 0;
  for (int g = 1; g <= N; g++) {
    if (!has[g]) {
      total += countPairs(g);
    }
  }
  return total;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  mobius_sieve();
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
