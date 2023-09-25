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

bool isprime(int x) {
  if (x <= 1) return false;
  for (int i = 2; i*i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}

bool check(vector<int> p) {
  vector<int> v;
  F0R(i, sz(p)) {
    v.push_back(abs(p[i] - (i+1)));
  }
  bool poss = true;
  for (auto x: v) {
    if (!isprime(x)) {
      poss = false;
      break;
    }
  }
  return poss;
}

void solve() {
  int N; cin >> N;
  int NN = N;
  if (N < 4) {
    cout << -1 << '\n';
  }
  else {
    vector<int> ans(N);
    while (N > 7) {
      ans[N-4] = N-1;
      ans[N-3] = N;
      ans[N-2] = N-3;
      ans[N-1] = N-2;
      N -= 4;
    }
    vector<int> arr;
    if (N == 4) {
      arr = {3, 4, 1, 2};
    }
    else if (N == 5) {
      arr = {3, 4, 5, 1, 2};
    }
    else if (N == 6) {
      arr = {3, 4, 5, 6, 2, 1};
    }
    else if (N == 7) {
      arr = {3, 4, 5, 6, 7, 1, 2};
    }
    else assert(0);
    for (int i = 0; i < N; i++) ans[i] = arr[i];
    F0R(i, NN) {
      cout << ans[i] << ' ';
    }
    cout << '\n';
    // assert(check(ans));
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // int N; cin >> N;
  // vector<int> p(N); iota(all(p), 1);
  // do {
  //   vector<int> v;
  //   F0R(i, N) {
  //     v.push_back(abs(p[i] - (i+1)));
  //   }
  //   bool poss = true;
  //   for (auto x: v) {
  //     if (!isprime(x)) {
  //       poss = false;
  //       break;
  //     }
  //   }
  //   if (poss) {
  //     cout << p << ' ' << v << endl;
  //   }
  // } while (next_permutation(all(p)));
  // return 0;
  int T; cin >> T;
  while (T--) solve();
}
