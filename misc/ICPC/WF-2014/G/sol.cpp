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

using vi = vector<int>;
struct TwoSat {
  int N;
  vector<vi> gr;
  // vi values; // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2*n) {}

  void either(int f, int j) {
    f = max(2*f, -1-2*f);
    j = max(2*j, -1-2*j);

    gr[f].push_back(j^1);
    gr[j].push_back(f^1);
  }

  vi val, comp, z; int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x; z.push_back(i);
    for(int e : gr[i]) if (!comp[e])
                         low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
        x = z.back(); z.pop_back();
        comp[x] = low;
        // if (values[x>>1] == -1)
        //   values[x>>1] = x&1;
      } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    // values.assign(N, -1);
    val.assign(2*N, 0); comp = val;
    FOR(i, 0, 2*N) if (!comp[i]) dfs(i);
    FOR(i, 0, N) if (comp[2*i] == comp[2*i+1]) return 0;
    return 1;
  }

  void reset() {
    F0R(i, 2*N) gr[i].clear();
    val.clear();
    comp.clear();
    z.clear();
    time = 0;
  }
};

int N;

vector<array<int, 3>> edges;
vector<int> D;

bool ok(int idx, int X, int Y, TwoSat& twosat) {
  twosat.reset();
  for (int i = idx; i < sz(edges); i++) {
    auto [w, a, b] = edges[i];
    twosat.either(~a, ~b);
    if (Y < w) {
      twosat.either(a, b);
    }
  }
  return twosat.solve();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  D.push_back(0);
  for (int i = 1; i <= N-1; i++) {
    for (int j = 1; j <= N-i; j++) {
      int a = i-1, b = i+j-1;
      int w; cin >> w;
      D.push_back(w);
      edges.push_back({w, a, b});
    }
  }
  sort(all(edges));
  sort(all(D)); D.erase(unique(all(D)), D.end());

  int X = 0;
  int ans = 2e9;

  TwoSat twosat(N);
  int idx = 0; while (idx < sz(edges) && edges[idx][0] <= D[X]) idx++;
  for (int Y = sz(D)-1; Y >= 0; Y--) {
    while (X <= Y && !ok(idx, D[X], D[Y], twosat)) {
      X++;
      while (idx < sz(edges) && edges[idx][0] <= D[X]) idx++;
    }
    if (X <= Y) ckmin(ans, D[X] + D[Y]);
    else break;
  }
  cout << ans << '\n';
}
