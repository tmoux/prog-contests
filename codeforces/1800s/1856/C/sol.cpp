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
  int N; cin >> N;
  int K; cin >> K;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  int ans = *max_element(all(A));
  F0R(i, N-1) {
    int lo = A[i], hi = A[i] + K + 1;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      ll need = 0;

      bool poss = true;
      for (int j = i; j < N; j++) {
        int cur = mid - (j - i);
        if (A[j] >= cur) {
          break;
        }
        else {
          if (j == N-1) {
            poss = false;
            break;
          }
          else need += cur - A[j];
        }
      }
      // cout << "checking " << mid << ": " << (poss && need <= K) << endl;
      // DEBUG(need);
      // DEBUG(poss);
      if (poss && need <= K) {
        lo = mid;
      }
      else hi = mid;
    }
    // cout << i << ": " << lo << endl;
    ckmax(ans, lo);
    // vector<int> B = A;
    // int left = K;
    // for (int j = i; j >= 0; j--) {
    //   int add = max(0, min(left, B[j+1]+1 - B[j]));
    //   B[j] += add;
    //   left -= add;
    //   ckmax(ans, B[j]);
    // }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
