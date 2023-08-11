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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> negs(n+1, 0), twos(n+1, 0);

    vector<int> zeros;
    zeros.push_back(0);
    FOR(i, 1, n+1) {
      cin >> a[i];
      if (a[i] == 0) zeros.push_back(i);
      if (a[i] < 0) negs[i] = 1;
      negs[i] += negs[i-1];
      if (abs(a[i]) == 2) twos[i] = 1;
      twos[i] += twos[i-1];
    }
    zeros.push_back(n+1);
    pair<int, array<int, 2>> ans = {0, {n, 0}};
    for (int i = 0; i < sz(zeros)-1; i++) {
      int L = zeros[i] + 1;
      int R = zeros[i+1] - 1;
      if (L > R) continue;
      for (int j = L; j <= R; j++) {
        if ((negs[R] - negs[j-1]) % 2 == 0) {
          ckmax(ans, {twos[R] - twos[j-1], {j-1, n-R}});
        }
        if ((negs[j] - negs[L-1]) % 2 == 0) {
          ckmax(ans, {twos[j] - twos[L-1], {L-1, n-j}});
        }
      }
    }

    cout << ans.second[0] << ' ' << ans.second[1] << '\n';
    // cout << "cnt " << ans.first << endl;

    // ans is at least 1 (delete everything)
    // delete all zeros--try every range between 2 consecutive zeros
    // if total # of negatives is even: then product is maximized (best is # of 2s
    // else, we need to 
  }
}
