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

ll solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N);
  FOR(i, 1, N) cin >> A[i];
  vector<int> sA = A;
  vector<int> B(N);
  F0R(i, N) cin >> B[i];
  sort(all(B));

  auto check = [&](int x, int k) -> bool {
    int j = 0;
    F0R(i, k) {
      while (j < N && B[j] <= sA[i]) j++;
      if (j == N) return false;
      else j++;
    }
    return true;
  };

  auto calc = [&](int x) -> int {
    int lo = 0, hi = N+1;
    sA = A;
    sA[0] = x;
    sort(all(sA));
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (check(x, mid) ? lo : hi) = mid;
    }
    return N - lo;
  };

  int c1 = calc(1);
  if (c1 == calc(M)) {
    return 1LL * M * c1;
  }
  else {
    int lo = 1, hi = M;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (calc(mid) == c1 ? lo : hi) = mid;
    }
    return 1LL * c1 * lo + 1LL * (c1 + 1) * (M - lo);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
