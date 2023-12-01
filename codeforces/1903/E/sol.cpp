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

// Divide points into two groups, based on parity of (x + y).
// Let X be the number of points in the same group as start, Y be number of points in other group.
// Claim: the strategy is to always just pick a point in the other group.
// P0 wins if X >= Y, P1 wins if X < Y.

void solve() {
  int N; cin >> N;
  int sx, sy; cin >> sx >> sy;
  int S = (sx ^ sy) & 1;
  int T = S ^ 1;

  array<int, 2> C = {0, 0};
  array<set<int>, 2> V;
  F0R(i, N) {
    int x, y; cin >> x >> y;
    C[(x^y)&1]++;
    V[(x^y)&1].insert(i+1);
  }

  auto get = [&](int s) -> int {
    assert(!V[s].empty());
    auto p = *V[s].begin(); V[s].erase(V[s].begin());
    return p;
  };

  auto erase = [&](int i) -> void {
    if (V[0].count(i)) V[0].erase(i);
    else if (V[1].count(i)) V[1].erase(i);
    else assert(false);
  };

  if (C[S] >= C[T]) {
    // play as P0
    cout << "First" << endl;
    for (int i = 0; i < N; i++) {
      if (i % 2 == 0) {
        if (!V[T].empty()) cout << get(T) << endl;
        else cout << get(S) << endl;
      }
      else {
        int j; cin >> j;
        erase(j);
      }
    }
  }
  else {
    // play as P1
    cout << "Second" << endl;
    for (int i = 0; i < N; i++) {
      if (i % 2 == 1) {
        if (!V[S].empty()) cout << get(S) << endl;
        else cout << get(T) << endl;
      }
      else {
        int j; cin >> j;
        erase(j);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
