#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}

const int maxn = 5002;
int spf[maxn];

vector<int> primes;
void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) {
    if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
    if (spf[i] == i) primes.push_back(i);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  int N; cin >> N;
  vector<int> cnt(maxn);
  vector<bool> on(maxn);
  F0R(i, N) {
    int x; cin >> x;
    cnt[x]++;
    on[x] = 1;
  }

  ll ans = 0;
  F0Rd(idx, sz(primes)) {
    int p = primes[idx];
    int s = 5000;
    vector<int> P(s+2);
    vector<int> K(maxn);
    for (int i = 0; i <= 5000; i++) {
      int mult = p;
      while (i/mult > 0) {
        K[i] += i/mult;
        mult *= p;
      }
      ans += 1LL * cnt[i] * K[i];
    }
    for (int i = 0; i <= 5000; i++) {
      if (on[i]) {
        int k = K[i];
        P[1] += cnt[i];
        P[k+1] -= cnt[i];
      }
    }
    int take = 0;
    for (int j = 1; j <= s; j++) {
      P[j] += P[j-1];
      if (P[j] * 2 > N) {
        take = j;
      }
      else break;
    }
    if (take > 0) {
      // cout << "taking " << p << ' ' << take << endl;
      assert(P[take] * 2 > N);
      ans += 1LL * take * (N - P[1]);
      for (int j = 1; j < take; j++) {
        ans -= 1LL * j * (P[j] - P[j+1]);
        ans += 1LL * (take - j) * (P[j] - P[j+1]);
      }
      ans -= 1LL * take * P[take];
    }
    for (int i = 0; i <= 5000; i++) {
      if (on[i]) {
        int k = K[i];
        if (k != take) on[i] = 0;
      }
    }
  }
  cout << ans << '\n';
}
