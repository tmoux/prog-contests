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

map<ll, pair<ll, ll>> s;
map<ll, int> toidx;

bool solve() {
  int N; cin >> N;
  vector<ll> A(N);
  F0R(i, N) cin >> A[i];
  ll sum = std::accumulate(all(A), 0LL);
  if (sum % N != 0) return false;
  ll T = sum / N;
  vector<int> cntS(31), cntT(31), cntDS(31), cntDT(31);
  F0R(i, N) {
    ll d = T - A[i];
    if (d == 0) continue;
    if (!s.count(d)) return false;
    auto [a, b] = s[d];
    if (toidx.count(d)) {
      int idx = toidx[d] + 1;
      cntDT[idx]++;
    }
    else if (toidx.count(-d)) {
      int idx = toidx[-d];
      cntDS[idx]++;
    }
    else {
      cntS[a]++;
      cntT[b]++;
    }
  }

  for (int k = 30; k >= 0; k--) {
    cntT[k] += cntDS[k];
    if (cntS[k] > cntT[k]) {
      if (k == 0 || cntDS[k-1] < cntS[k] - cntT[k]) return false;
      int take = cntS[k] - cntT[k];
      cntDS[k-1] -= take;
      cntS[k-1] += take;
      cntT[k] += take;
    }
    if (cntT[k] < cntS[k] || cntDT[k] < cntT[k] - cntS[k]) return false;
    int take = cntT[k] - cntS[k];
    cntS[k] += take;
    if (k > 0) {
      cntT[k-1] += take;
      cntS[k-1] += cntDT[k] - take;
    }
    cntDS[k] = cntDT[k] = 0;
  }

  F0R(i, 31) if (cntS[i] != cntT[i]) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  F0R(i, 31) {
    toidx[1LL << i] = i;
    F0R(j, 31) {
      ll d = (1LL << i) - (1LL << j);
      s[d] = {i, j};
    }
  }
  int T; cin >> T;
  while (T--) cout << (solve() ? "Yes" : "No") << '\n';
}
