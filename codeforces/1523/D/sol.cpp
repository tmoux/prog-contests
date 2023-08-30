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
  int N, M, P; cin >> N >> M >> P;
  vector<int> cnt(M);
  vector<vector<int>> A(N, vector<int>(M));
  F0R(i, N) {
    string s; cin >> s;
    F0R(j, M) {
      A[i][j] = s[j] - '0';
      if (A[i][j]) cnt[j]++;
    }
  }
  int maj = (N + 1) / 2;

  pair<int, ll> best = {0, 0};
  REP(50) {
    int idx = rng() % N;
    vector<int> pos;
    F0R(j, M) if (A[idx][j]) pos.push_back(j);

    vector<int> C(1 << sz(pos));
    vector<int> F(1 << sz(pos));
    F0R(i, N) {
      int mask = 0;
      F0R(j, sz(pos)) {
        mask |= (1 ^ A[i][pos[j]]) << j;
      }
      C[mask]++;
      F[mask]++;
    }
    for (int i = 0; i < sz(pos); i++) {
      F0R(mask, 1 << sz(pos)) {
        if (mask & (1 << i)) {
          F[mask] += F[mask ^ (1 << i)];
        }
      }
    }

    int ALL = (1 << sz(pos)) - 1;
    F0R(mask, 1 << sz(pos)) {
      if (F[mask] >= maj) {
        int x = mask ^ ALL;
        ll tr = 0;
        F0R(j, sz(pos)) {
          if (x & (1 << j)) {
            tr |= 1LL << pos[j];
          }
        }
        ckmax(best, {__builtin_popcount(x), tr});
      }
    }
  }

  F0R(j, M) {
    cout << ((best.second >> j) & 1);
  }
  cout << '\n';
}
