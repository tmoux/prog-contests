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

const int maxn = 5e5+5;

int N, Q;
struct Query {
  int t, L, R, X, V, Y;
};

Query queries[maxn];

const int BLK = 400;
ll A[maxn];

vector<array<int, 4>> CUR;


ll add[maxn];
void rebuild() {
  fill(add, add + N, 0);
  for (auto [L, R, X, V]: CUR) {
  }
  for (int i = 1; i <= N; i++) {
    A[i] += add[i] - add[max(0, i - BLK)];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  bool has_type2 = false;
  F0R(i, Q) {
    int t; cin >> t;
    if (t == 1) {
      int L, R, X, V; cin >> L >> R >> X >> V;
      queries[i] = {1, L, R, X, V};
    }
    else if (t == 2) {
      int L, R, X, V; cin >> L >> R >> X >> V;
      queries[i] = {2, L, R, X, V};
      has_type2 = true;
    }
    else {
      int Y; cin >> Y;
      queries[i].t = 3;
      queries[i].Y = Y;
    }
  }

  F0R(i, Q) {
    auto [t, L, R, X, V, Y] = queries[i];
    if (t == 1) {
      if (X >= BLK) {
        for (int i = L; i <= R; i += X) {
          A[i] += V;
        }
      }
      else {

      }
    }
    else if (t == 2) assert(false);
    else {
      ll ans = A[Y];
      for (auto [L, R, X, V]: CUR) {
        if (Y % X == L % X && L <= Y && Y <= R) {
          ans += V;
        }
      }
      cout << ans << '\n';
    }
    if (sz(CUR) >= BLK) {
      rebuild();
    }
  }
}
