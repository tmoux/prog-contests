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

int A[2005];
ll cost = 0;

int ask(int l, int r) {
  if (l == r) return 0;
  cout << "? " << l << ' ' << r << endl;

  int res; cin >> res;
  // cost += (r - l) * (r - l);
  // int res = 0;
  // for (int i = l; i <= r; i++) {
  //   for (int j = i+1; j <= r; j++) {
  //     if (A[i] > A[j]) res++;
  //   }
  // }
  return res;
}

void solve() {
  int N; cin >> N;
  // for (int i = 1; i <= N; i++) cin >> A[i];
  // cost = 0;
  vector<int> cands(N);
  iota(all(cands), 1);
  auto find_max = y_combinator([&](auto find_max, vector<int> v) -> int {
    if (v.empty()) return -1;
    if (sz(v) == 1) return v[0];
    vector<int> v1, v2;
    for (int i = 0; i < sz(v); i++) {
      (i < sz(v) / 2 ? v1 : v2).push_back(v[i]);
    }
    int a = find_max(v1);
    int b = find_max(v2);
    if (a == -1) return b;
    else if (b == -1) return a;
    else {
      int c = ask(a, b-1);
      int d = ask(a, b);
      return c == d ? b : a;
    }
  });

  int ans = find_max(cands);
  cout << "! " << ans << endl;
  // cerr << "cost " << cost << ": " << 5 * N * N << endl;
  // assert(cost <= 5 * N * N);
  //
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
