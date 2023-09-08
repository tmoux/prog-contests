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

typedef long double ld;

ll ceildiv(ll a, ll b) {
  return (a + b - 1) / b;
}

struct FN
{
  ll m, b; //in this case, function is a line
  FN(ll _m, ll _b) : m(_m), b(_b) {}
  ll eval(ll x) const {
    return m*x + b;
  }

  ld intersect(const FN& r) const { //returns x coordinate of intersection
    //assert(m != r.m);
    return (ld)(r.b-b)/(ld)(m-r.m);
  }

  friend bool comp(const FN& l1, const FN& l2, const FN& l) {
    //order in deque: l1, l2, l
    //true --> l2 is unnecessary
    ld x1 = l1.intersect(l);
    ld x2 = l1.intersect(l2);
    return x1 <= x2;
  }
};

struct Hull: public deque<FN> //convex hull for maximum
{
  void addFN(const FN& l) {
    while (size() >= 2 &&
           comp((*this)[size()-2],(*this)[size()-1],l)) {
      this->pop_back();
    }
    this->push_back(l);
  }

  ll query(ll x) {
    if (size() == 0) return -(1LL<<62); //handle empty hull
    while (size() >= 2 && (*this)[1].eval(x) >= (*this)[0].eval(x)) {
      pop_front();
    }
    return (*this)[0].eval(x);
  }

  ld getNextIntersection() {
    assert(size() > 1);
    return (*this)[0].intersect((*this)[1]);
  }

  ll getMinTime(ll c) {
    assert(!empty());
    ll m = (*this)[0].m;
    ll b = (*this)[0].b;
    return max((ll)0, ceildiv(c - b, m));
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  long long target; cin >> target;
  vector<pair<ll, ll>> v;
  long long mxStart = 0;
  F0R(i, N) {
    long long a, b; cin >> a >> b;
    if (b == 0) ckmax(mxStart, a);
    else v.emplace_back(a, b);
  }
  assert(mxStart > 0);
  ll ans = ceildiv(target, mxStart);
  Hull hull;
  hull.addFN(FN(mxStart, 0));
  sort(all(v));
  vector<pair<ll, ll>> st = {{mxStart, 0}};
  for (auto [m, c]: v) {
    if (m <= st.back().first) continue;
    while (st.back().second >= c) st.pop_back();
    st.emplace_back(m, c);
  }
  for (auto [m, c]: st) {
    while (sz(hull) >= 2 && hull.getNextIntersection() <= hull.getMinTime(c)) {
      hull.pop_front();
    }
    ll t = hull.getMinTime(c);
    ll b = hull.query(t) - c;
    assert(b >= 0);
    if (b <= target) ckmin(ans, t + ceildiv(target - b, m));
    hull.addFN(FN(m, b - t * m));
  }
  long long res = ans;
  cout << res << '\n';
}
