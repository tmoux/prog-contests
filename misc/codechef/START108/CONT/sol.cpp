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
  F0R(i, N) {
    cin >> A[i];
  }
  vector<pair<int, int>> v;
  vector<int> B(N-1);
  F0R(i, N-1) {
    B[i] = abs(A[i+1] - A[i]) - 1;
    v.push_back({B[i], i});
  }
  sort(all(v), [&](auto a, auto b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
  });
  set<int> s; s.insert(-1); s.insert(N-1);
  ll ans = 1LL * N * (N + 1) / 2;
  for (auto [x, i]: v) {
    if (x > 1) {
      auto it = s.lower_bound(i);
      int l = i - *prev(it) - 1;
      int r = *it - i - 1;

      auto prog = [](int a, int b) {
        if (a > b) return 0LL;
        return 1LL * (a + b) * (b - a + 1) / 2;
      };
      int k = min(i+r, max(i-1, i - l + x - 2));
      ans -= 1LL * max(0, k - i + 1) * (l + 1);
      ans -= prog(max(0, i - (i+r - x + 2) + 1), i - (k+1 - x + 2) + 1);
    }
    s.insert(i);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
