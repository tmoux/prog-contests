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

const ll INF = LLONG_MAX;
struct Tracker {
  ll mn, mx, t;
  vector<ll> v;
  Tracker(ll x, ll _t) {
    mn = mx = x;
    t = _t;
    v.push_back(x);
  }

  void add(ll x) {
    ckmin(mn, x);
    ckmax(mx, x);
    v.push_back(x);
  }

  ll query(ll x) {
    return min((mn + t) * x + t * mn,
               (mx + t) * x + t * mx);
  }
};

ll solvePos(int N, vector<ll> A) {
  sort(all(A), greater());
  ll sum = std::accumulate(all(A), 0LL);
  sum += A[N-1] * (N - 2);
  if (sum > 0) return INF;
  auto calc = [&](ll t) -> ll {
    Tracker LC(A[0], t);

    ll mst = 0;
    for (int l = 1, r = N-1; l <= r;) {
      ll ql = LC.query(A[l]), qr = LC.query(A[r]);
      if (ql <= qr) {
        // remove min
        mst += ql;
        LC.add(A[l++]);
      }
      else {
        // remove max
        mst += qr;
        LC.add(A[r--]);
      }
    }
    return mst;
  };
  ll lo = -1, hi = 2e6;
  while (lo + 1 < hi) {
    ll mid = (lo + hi) / 2;
    if (calc(mid) > calc(mid+1)) {
      hi = mid;
    }
    else lo = mid;
  }
  return calc(hi);
}

void solve() {
  int N; cin >> N;
  vector<ll> A(N), B(N);
  F0R(i, N) {
    cin >> A[i];
    B[i] = -A[i];
  }
  ll ans = max(solvePos(N, A), solvePos(N, B));
  if (ans < INF) {
    cout << ans << '\n';
  }
  else cout << "INF" << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
