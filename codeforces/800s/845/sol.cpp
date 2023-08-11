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

template<typename T = uint32_t, int LOG_A = 30>
struct XorBasis {
  T basis[LOG_A];
  XorBasis() {
    fill(basis, basis+LOG_A, 0);
  }

  void insertVector(T mask) {
    for (int i = LOG_A - 1; i >= 0; i--) {
      if ((mask & 1 << i) == 0) continue;
      if (!basis[i]) {
        basis[i] = mask;
        return;
      }
      mask ^= basis[i];
    }
  }

  T maxXor(T x) { // maximum z s.t. x ^ y = z, where y in span
    T ans = x;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (basis[i] && !(ans & (1 << i))) ans ^= basis[i];
    }
    return ans;
  }

  T minXor(T x) { // maximum z s.t. x ^ y = z, where y in span
    T ans = x;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (basis[i] && (ans & (1 << i))) ans ^= basis[i];
    }
    return ans;
  }
};

const int maxn = 1e5+5;
int N, M;
vector<array<int, 3>> adj[maxn];

XorBasis<uint64_t, 60> xb;

int P[maxn];
bool vis[maxn], intree[maxn];
void dfs(int i) {
  vis[i] = 1;
  for (auto [j, w, id]: adj[i]) {
    if (vis[j]) continue;
    intree[id] = 1;
    P[j] = P[i] ^ w;
    dfs(j);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  vector<array<int, 4>> edges;
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    edges.push_back({a, b, w, i});
    adj[a].push_back({b, w, i});
    adj[b].push_back({a, w, i});
  }

  dfs(1);

  for (auto [a, b, w, id]: edges) {
    if (!intree[id]) {
      int cyc = P[a] ^ P[b] ^ w;
      xb.insertVector(cyc);
    }
  }

  cout << xb.minXor(P[N]) << '\n';
}
