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

using P = pair<ll, ll>;

P dist(P A, P B) {
  return {B.first - A.first, B.second - A.second};
}

ll manhat(P A, P B) {
  return abs(B.first - A.first) + abs(B.second - A.second);
}

ll movedist(P A, P B, P T) {
  if (A.first == B.first && B.first == T.first &&
      ((A.second < B.second && B.second < T.second) ||
       (A.second > B.second && B.second > T.second))) {
    return manhat(A, T) + 2;
  }
  else if (A.second == B.second && B.second == T.second &&
           ((A.first < B.first && B.first < T.first) ||
            (A.first > B.first && B.first > T.first))) {
    return manhat(A, T) + 2;
  }
  else return manhat(A, T);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  P A, B, C;
  cin >> A.first >> A.second;
  cin >> B.first >> B.second;
  cin >> C.first >> C.second;

  P delta = dist(B, C);
  ll ans = 0;
  if (delta.first == 0) {
    P T = {B.first, delta.second > 0 ? B.second - 1 : B.second + 1};
    ans += movedist(A, B, T);
    ans += manhat(B, C);
  }
  else if (delta.second == 0) {
    P T = {delta.first > 0 ? B.first - 1 : B.first + 1, B.second};
    ans += movedist(A, B, T);
    //DEBUG(delta);
    //DEBUG(T);
    //DEBUG(ans);
    ans += manhat(B, C);
  }
  else {
    P T1 = {B.first, delta.second > 0 ? B.second - 1 : B.second + 1};
    P T2 = {delta.first > 0 ? B.first - 1 : B.first + 1, B.second};

    ll minans = 1e18;
    for (auto v: vector<vector<P>>{{T1, T2}, {T2, T1}}) {
      ll tr = 0;

      tr += movedist(A, B, v[0]);
      tr += 2;
      tr += manhat(B, C);
      ckmin(minans, tr);
    }
    ans = minans;
  }
  cout << ans << '\n';
}
