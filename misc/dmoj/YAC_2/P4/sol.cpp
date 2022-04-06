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

const int maxn = 2005;
int N;
ll M;
ll A[maxn];

vector<ll> f(int i) {
  vector<ll> pc(N);
  F0R(j, N) if (i != j) {
    ckmax(pc[j], (A[i] + A[j]) % M);
    if (A[i] >= A[j]) ckmax(pc[j], (A[i] - A[j]) % M);
    else if (A[j] >= A[i]) ckmax(pc[j], (A[j] - A[i]) % M);
    ckmax(pc[j], (A[i] * A[j]) % M);
    if (A[i] >= A[j] && ((A[i] % A[j]) == 0)) ckmax(pc[j], (A[i] / A[j]) % M);
    else if (A[j] >= A[i] && ((A[j] % A[i]) == 0)) ckmax(pc[j], (A[j] / A[i]) % M);
  }
  return pc;
}

bool vis[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) cin >> A[i];

  // run Prim's
  ll ans = 0;
  vis[0] = true;

  auto dist = f(0);
  REP(N-1) {
    pair<ll, int> best = {-1, -1};
    F0R(i, N) if (!vis[i]) {
      ckmax(best, {dist[i], i});
    }
    int i = best.second;

    vis[i] = true;
    ans += best.first;
    auto pc = f(i);
    F0R(j, N) if (!vis[j]) ckmax(dist[j], pc[j]);
  }
  cout << ans << '\n';
}
