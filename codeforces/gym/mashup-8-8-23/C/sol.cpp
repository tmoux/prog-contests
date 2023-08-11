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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<uint64_t> H(N+1);
  FOR(i, 1, N+1) H[i] = rng();
  vector<uint64_t> pfx(N+1);
  set<uint64_t> S;
  FOR(i, 1, N+1) {
    pfx[i] = H[i] ^ pfx[i-1];
    S.insert(pfx[i]);
  }

  vector<int> A(N+1);
  ll ans = 0;
  FOR(i, 1, N+1) {
    cin >> A[i];
    if (A[i] == 1) ans++;
  }

  for (int z = 0; z < 2; z++) {
    reverse(A.begin() + 1, A.begin() + N + 1);
    vector<uint64_t> P(N+1);
    FOR(i, 1, N+1) P[i] = H[A[i]] ^ P[i-1];
    vector<int> L(N+1);
    vector<int> prev(N+1, 0);
    FOR(i, 1, N+1) {
      L[i] = max(L[i-1], prev[A[i]] + 1);
      prev[A[i]] = i;
    }

    y_combinator([&](auto F, int l, int r) -> void {
      if (l == r) return;
      int mid = (l + r) >> 1;
      mid = (l + r) % 2 == 0 ? (z == 0 ? mid : mid-1) : mid;
      F(l, mid);
      F(mid+1, r);

      int mx = 0;
      for (int i = mid+1; i <= r; i++) {
        ckmax(mx, A[i]);
        if (l <= i-mx+1 && i-mx+1 <= mid && L[i] <= i-mx+1) {
          if (S.count(P[i] ^ P[i-mx])) {
            ans++;
          }
        }
      }
    })(1, N);
  }
  cout << ans << '\n';
}
