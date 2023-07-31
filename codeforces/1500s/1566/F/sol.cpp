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

struct Tracker {
  using P = pair<ll, ll>;
  vector<P> smaller, bigger;
  ll smallerSum = 1e18;
  int idx = 0;
  void add(ll x, ll c) {
    smaller.push_back({x, 2*x + c});
    bigger.push_back({x, x + c});
  }
  void init() {
    assert(!smaller.empty());
    reverse(all(smaller));
    reverse(all(bigger));
    for (int i = 1; i < sz(smaller); i++) {
      ckmin(smaller[i].second, smaller[i-1].second);
    }
    for (int i = sz(bigger)-2; i >= 0; i--) {
      ckmin(bigger[i].second, bigger[i+1].second);
    }
  }
  ll query(ll y) { // y is increasing
    while (idx < sz(smaller) && smaller[idx].first < y) {
      idx++;
    }
    const ll inf = 1e18;
    return min(y + (idx > 0 ? smaller[idx-1].second : inf),
               2*y + (idx < sz(bigger) ? bigger[idx].second : inf));
  }
};

ll solve() {
  int N, M; cin >> N >> M;
  const int INF = 2e9;
  vector<int> A(N);
  set<int> points;
  F0R(i, N) {
    cin >> A[i];
    points.insert(A[i]);
  }
  sort(all(A)); A.push_back(INF);
  vector<array<int, 2>> I;
  REP(M) {
    int l, r; cin >> l >> r;
    auto it = points.lower_bound(l);
    if (it != points.end() && *it <= r) {}
    else I.push_back({l, r});
  }
  sort(all(I)); I.erase(unique(all(I)), I.end());
  M = sz(I);

  vector<map<int, ll>> dp(N);
  int idx = 0;
  F0R(i, N) {
    Tracker tracker;
    if (i == 0) {
      int mnR = A[i];
      while (idx < M && I[idx][0] < A[i]) {
        ckmin(mnR, I[idx++][1]);
      }
      tracker.add(A[i] - mnR, 0);
    }
    else {
      for (auto [x, c]: dp[i-1]) {
        tracker.add(A[i] - x, c);
      }
    }
    tracker.init();

    vector<array<int, 2>> myIs;
    set<pair<int, int>> rights;
    while (idx < M && I[idx][0] < A[i+1]) {
      rights.insert({I[idx][1], I[idx][0]});
      myIs.push_back(I[idx++]);
    }

    if (myIs.empty()) {
      dp[i][A[i+1]] = tracker.query(0);
    }
    else {
        int y = rights.begin()->first;
        dp[i][y] = tracker.query(0);
      for (auto [l, r]: myIs) {
        rights.erase({r, l});
        int y = rights.empty() ? A[i+1] : rights.begin()->first;
        if (dp[i].count(y)) ckmin(dp[i][y], tracker.query(l - A[i]));
        else dp[i][y] = tracker.query(l - A[i]);
      }
    }
  }
  return dp[N-1][INF];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
