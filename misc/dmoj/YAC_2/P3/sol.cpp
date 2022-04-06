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

const int maxn = 3e6+6;
const int maxx = 1e6+6;
int N, K;
int h[maxn];

int spf[maxx];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxx; i++) if (!spf[i]) {
    for (int j = i; j < maxx; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

map<int, vector<int>> primes;

int count_moves(const vector<int>& v) {
  auto check = [&](int k) {
    int cnt = 0;
    for (auto c: v) {
      cnt += min(k, c);
    }
    return cnt >= 1LL * k * K;
  };
  int lo = 0, hi = 25 * N;  
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    (check(mid) ? lo : hi) = mid;
  }
  return lo;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N >> K;

  F0R(i, N) {
    int x; cin >> x;
    map<int, int> cnt;
    while (x > 1) {
      cnt[spf[x]]++;
      x /= spf[x];
    }
    for (auto [p, c]: cnt) {
      primes[p].push_back(c);
    }
  }

  int ans = 0;
  for (auto& [p, v]: primes) {
    ans += count_moves(v);
  }
  cout << ans << '\n';
}
