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
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  sort(all(A));

  auto calc = [&](int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;
    else return (x + 1) / 2 + 1;
  };
  ll ans = 0;
  int j = 0;
  for (int i = N-1; i >= 0; i--) {
    if (j > i) break;
    if (i == j) {
      ans += calc(A[i]);
      break;
    }
    int sum = 0;
    while (j < i && sum < A[i]) {
      int take = min(A[j], A[i] - sum);
      sum += take;
      A[j] -= take;
      if (A[j] == 0) j++;
    }
    if (sum == A[i]) {
      ans += sum + 1;
    }
    else {
      int tot = sum + A[i];
      int take = tot / 2 - sum;
      A[i] -= tot / 2 + take;
      ans += tot / 2 + 1;
      ans += calc(A[i]);
      break;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
