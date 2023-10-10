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

bool solve() {
  int N; cin >> N;
  string X, Y; cin >> X >> Y;

  auto check = [&](int l, int r) -> bool {
    if (l > r) return true;
    int cA = 0, cB = 0, tA = 0, tB = 0;
    for (int i = l; i <= r; i++) {
      if (X[i] == 'A') cA++;
      else if (X[i] == 'B') cB++;

      if (Y[i] == 'A') tA++;
      else if (Y[i] == 'B') tB++;
    }
    if (cA > tA || cB > tB) return false;
    int x = tA - cA, y = tB - cB;
    for (int i = l; i <= r; i++) {
      if (X[i] == 'C') {
        if (x > 0) {
          X[i] = 'A';
          x--;
        }
        else {
          X[i] = 'B';
          y--;
        }
      }
    }

    int cX = 0, cY = 0;
    for (int i = l; i <= r; i++) {
      if (X[i] == 'A') cX++;
      if (Y[i] == 'A') cY++;
      if (cX < cY) return false;
    }
    return true;

    // set<int> s;
    // for (int i = l; i <= r; i++) {
    //   if (X[i] == 'B' || X[i] == 'C') s.insert(i);
    // }
    // for (int i = l; i <= r; i++) {
    //   if (s.count(i)) s.erase(i);
    //   if (Y[i] == 'B') {
    //     if (X[i] == 'B' || X[i] == 'C') continue;
    //     else {
    //       if (s.empty()) return false;
    //       else {
    //         int j = *s.begin(); s.erase(s.begin());
    //         X[j] = 'A';
    //       }
    //     }
    //   }
    //   else if (Y[i] == 'A') {
    //     if (X[i] == 'A' || X[i] == 'C') continue;
    //     else return false;
    //   }
    //   else assert(false);
    // }
    // return true;
  };

  vector<int> v = {-1};
  F0R(i, N) {
    if (Y[i] == 'C') {
      if (X[i] != 'C') return false;
      else {
        v.push_back(i);
      }
    }
  }
  v.push_back(N);
  bool poss = true;
  F0R(i, sz(v)-1) {
    poss &= check(v[i] + 1, v[i+1] - 1);
  }

  return poss;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << (solve() ? "Yes" : "No") << '\n';
}
