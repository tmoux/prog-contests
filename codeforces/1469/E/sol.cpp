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
  const int B = 20;
  int N, K; cin >> N >> K;
  string s; cin >> s;
  for (char& c: s) c = c == '1' ? '0' : '1';
  vector<int> A(N+1), P(N+1);
  F0R(i, N) {
    A[i+1] = s[i] - '0';
    P[i+1] = A[i+1] + P[i];
  }

  const int MX = K > B ? N+1 : min(N+1, 1 << K);
  vector<int> cnt(MX);
  int cur = 0;
  for (int i = K; i >= max(1, K - B + 1); i--) {
    cur += A[i] * (1 << (K - i));
  }
  for (int i = K; i <= N; i++) {
    if ((K > B && P[i-B] - P[i-K] > 0) || cur >= MX) {} // too big
    else {
      cnt[cur]++;
    }
    if (i + 1 <= N) {
      if (A[i-min(B, K)+1] == 1)
        cur -= 1 << (min(B, K) - 1);
      cur = (cur << 1) | A[i+1];
    }
  }
  for (int i = 0; i < MX; i++) {
    if (cnt[i] == 0) {
      cout << "YES\n";
      vector<int> ans;
      REP(K) {
        ans.push_back(i % 2);
        i /= 2;
      }
      F0Rd(j, K) {
        cout << ans[j];
      }
      cout << '\n';
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
