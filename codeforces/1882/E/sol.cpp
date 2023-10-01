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

vector<int> op(const vector<int>& v, int i) {
  vector<int> r;
  for (int j = i+1; j < sz(v); j++) r.push_back(v[j]);
  r.push_back(v[i]);
  for (int j = 0; j < i; j++) r.push_back(v[j]);
  return r;
}

vector<int> solve(vector<int> v) {
  int n = sz(v);
  vector<int> ops;
  for (int i = 1; i <= n-1; i++) {
    int pos = -1;
    for (int j = 0; j < n; j++) {
      if (v[j] == i) {
        pos = j;
        break;
      }
    }
    assert(pos != -1);
    if (pos != n-1) {
      ops.push_back(pos+1);
      v = op(v, pos+1);
    }
    pos = -1;
    for (int j = 0; j < n; j++) {
      if (v[j] == i+1) {
        pos = j;
        break;
      }
    }
    assert(pos != -1);
    v = op(v, pos);
    ops.push_back(pos);
    // cout << i << ": " << v << endl;
  }
  // DEBUG(v);
  for (int i = 0; i < n; i++) assert(v[i] == i+1);
  // DEBUG(ops);
  return ops;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<int> A(N), B(M);
  F0R(i, N) cin >> A[i];
  F0R(i, M) cin >> B[i];

  auto v1 = solve(A);
  auto v2 = solve(B);

  // DEBUG(v1);
  // DEBUG(v2);

  if (N % 2 == 0 && M % 2 == 0 && (sz(v1) % 2) != (sz(v2) % 2)) {
    cout << -1 << '\n';
  }
  else {
    if ((sz(v1) % 2) != (sz(v2) % 2)) {
      if (N % 2 == 1) {
        REP(N) v1.push_back(0);
      }
      else if (M % 2 == 1) {
        REP(M) v2.push_back(0);
      }
      else assert(false);
    }
    while (sz(v1) < sz(v2)) {
      v1.push_back(0);
      v1.push_back(N-1);
    }
    while (sz(v2) < sz(v1)) {
      v2.push_back(0);
      v2.push_back(M-1);
    }

    assert(sz(v1) == sz(v2));
    cout << sz(v1) << '\n';
    F0R(i, sz(v1)) {
      cout << v1[i]+1 << ' ' << v2[i]+1 << '\n';
    }
  }
}
