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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  string S; cin >> S;
  vector<array<int, 2>> P(N+1), R(N+1);
  map<char, array<int, 2>> mp = {
  {'U', {0, 1}},
  {'D', {0, -1}},
  {'L', {-1, 0}},
  {'R', {1, 0}},
  };

  auto add = [&](array<int, 2> a, array<int, 2> b) -> array<int, 2> {
    return {a[0] + b[0], a[1] + b[1]};
  };

  map<array<int, 2>, vector<int>> MP, MPR;
  P[0] = {0, 0};
  F0R(i, N) {
    P[i+1] = add(P[i], mp[S[i]]);
  }
  // cout << P << endl;
  for (int i = N-1; i >= 0; i--) {
    R[i] = add(R[i+1], mp[S[i]]);
  }
  // cout << R << endl;

  F0R(i, N+1) {
    MP[P[i]].push_back(i);
    MPR[R[i]].push_back(i);
  }

  F0R(t, Q) {
    int x, y, l, r; cin >> x >> y >> l >> r;
    bool poss = false;
    if (MP.count({x, y})) {
      const auto& v = MP[{x, y}];
      if (v.front() < l || v.back() >= r) poss = true;
    }

    int A = x - P[l-1][0] + R[r][0];
    int B = y - P[l-1][1] + R[r][1];

    if (MPR.count({A, B})) {
      const auto& v = MPR[{A, B}];
      auto it = lower_bound(all(v), l);
      if (it != v.end() && *it <= r) poss = true;
    }

    cout << (poss ? "YES" : "NO") << '\n';
  }
}
