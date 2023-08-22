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

int solve() {
  int N, M; cin >> N >> M;
  string s, t; cin >> s >> t;
  vector<int> pfx(N), sfx(N);
  {
    int j = 0;
    F0R(i, N) {
      if (j < M && s[i] == t[j]) {
        pfx[i] = (i == 0 ? 0 : pfx[i-1]) + 1;
        j++;
      }
      else pfx[i] = i == 0 ? 0 : pfx[i-1];
    }
    j = M-1;
    F0Rd(i, N) {
      if (j >= 0 && s[i] == t[j]) {
        sfx[i] = (i == N-1 ? 0 : sfx[i+1]) + 1;
        j--;
      }
      else sfx[i] = i == N-1 ? 0 : sfx[i+1];
    }
  }

  int lo = 0, hi = N;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    bool poss = false;

    F0R(i, N) {
      int a = i-1 >= 0 ? pfx[i-1] : 0;
      int b = i+mid < N ? sfx[i+mid] : 0;
      poss |= (a + b >= M) && a > 0 && b > 0;
      // if (a + b >= M && mid == 4) {
      //   cout << "HUH " << i << ' ' << a << ' ' << b << endl;
      // }
    }

    (poss ? lo : hi) = mid;
  }
  return lo+1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 1;
  while (T--) cout << solve() << '\n';
}
