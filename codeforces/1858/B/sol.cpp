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

void solve() {
  int N, M, D; cin >> N >> M >> D;
  vector<int> S(M);
  F0R(i, M) cin >> S[i];

  int min_ans = 2e9, num_ans = 0;
  int cur = 0;
  F0R(i, M) {
    int space = S[i] - (i == 0 ? 1 : S[i-1]) - 1;
    cur += space / D;
  }
  cur += (N - S[M-1]) / D;

  F0R(i, M) {
    int ncur;
    if (S[i] == 1) {
      ncur = cur + M;
      // num_ans = 1;
    }
    else {
      int s1 = S[i] - (i == 0 ? 1 : S[i-1]) - 1;
      int s2 = (i == M-1 ? N+1 : S[i+1]) - S[i] - 1;
      ncur = cur - s1/D - s2/D + (s1+s2+1)/D + (S[0] == 1 ? M-1 : M);
      // DEBUG(M);
      // DEBUG(cur - s1/D - s2/D + (s1+s2+1)/D + M);
      // cout << S[i] << ": " << ncur << endl;
    }
    if (ncur < min_ans) {
      min_ans = ncur;
      num_ans = 1;
    }
    else if (ncur == min_ans) {
      num_ans++;
    }
  }
  cout << min_ans << ' ' << num_ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
