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

// type 0: add interval
// type 1: query
struct Query {
  int b, l, id, ty;
  bool operator<(const Query& rhs) const {
    return b > rhs.b;
  };
};

void solve() {
  int N; cin >> N;
  vector<array<int, 2>> I(N);
  vector<Query> queries; // b, l, id
  F0R(i, N) {
    int l, r, a, b; cin >> l >> r >> a >> b;
    I[i] = {l, b};
    queries.push_back({b, l, i, 0});
  }
  int Q; cin >> Q;
  vector<int> ans(Q);
  F0R(i, Q) {
    int x; cin >> x;
    queries.push_back({x, -1, i, 1});
  }

  vector<int> mxR(N);
  sort(all(queries));
  set<pair<int, int>> removes; // l, id
  set<pair<int, int>> curMx; // mxR, id
  for (auto [b, l, id, ty]: queries) {
    while (!removes.empty() && removes.rbegin()->first > b) {
      auto [_, idx] = *removes.rbegin();
      removes.erase(prev(removes.end()));
      curMx.erase(curMx.find({mxR[idx], idx}));
    }
    if (ty == 0) {
      mxR[id] = curMx.empty() ? b : curMx.rbegin()->first;
      removes.insert({l, id});
      curMx.insert({mxR[id], id});
    }
    else {
      ans[id] = curMx.empty() ? b : curMx.rbegin()->first;
    }
  }

  F0R(i, Q) {
    cout << ans[i] << " \n"[i == Q-1];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
