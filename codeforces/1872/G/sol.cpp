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

void solve() {
  int N; cin >> N;
  vector<ll> A(N); for (auto& x: A) cin >> x;
  const ll MX = 5e5;
  ll prod = 1;
  for (auto x: A) {
    prod = min(MX, prod * x);
  }
  if (prod >= MX) {
    int l = 0; while (A[l] == 1) l++;
    int r = N-1; while (A[r] == 1) r--;
    cout << l+1 << ' ' << r+1 << '\n';
  }
  else {
    vector<ll> pfx(N);
    F0R(i, N) pfx[i] = A[i] + (i == 0 ? 0 : pfx[i-1]);
    auto getsum = [&](int l, int r) -> ll {
      return pfx[r] - (l == 0 ? l : pfx[l-1]);
    };

    vector<int> indices;
    F0R(i, N) if (A[i] > 1) indices.push_back(i);
    pair<ll, pair<int, int>> best = {pfx[N-1], {0, 0}};
    F0R(i, sz(indices)) {
      int l = indices[i];
      ll curprod = 1;
      FOR(j, i, sz(indices)) {
        int r = indices[j];
        curprod *= A[r];
        ll tr = pfx[N-1] - getsum(l, r) + curprod;
        ckmax(best, {tr, {l, r}});
      }
    }

    cout << best.second.first+1 << ' ' << best.second.second+1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
