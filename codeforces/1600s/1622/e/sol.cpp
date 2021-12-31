#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

void solve() {
  int n, m; cin >> n >> m;
  vector<int> expect(n);
  for (auto& i: expect) cin >> i;

  vector<string> answer(n);
  F0R(i, n) {
    cin >> answer[i];
  }

  vector<int> best_perm;
  int best_ans = -1;
  for (int mask = 0; mask < (1<<n); mask++) {
    vector<pair<int,int>> questions;
    F0R(j, m) {
      int w = 0;
      F0R(i, n) {
        w += (mask&(1<<i) ? 1 : -1) * (answer[i][j] - '0');
      }
      questions.push_back({w, j});
    }
    int tr = 0;
    F0R(i, n) {
      tr += (mask&(1<<i) ? -1 : 1) * expect[i];
    }
    sort(all(questions));
    vector<int> tr_perm(m);
    F0R(i, m) {
      tr_perm[questions[i].second] = i+1;
      tr += (i+1) * questions[i].first;
    }
    if (ckmax(best_ans, tr)) {
      best_perm = tr_perm;
    }
  }
  for (auto i: best_perm) {
    cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
