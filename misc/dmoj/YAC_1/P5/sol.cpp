#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

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
};

const int maxn = 1e5+5;
int N, Q;

pair<int,int> P[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // solve subtask 1: only lines, N, Q <= 1000
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    int s, v, a; cin >> s >> v >> a;
    assert(a == 0);
    P[i] = {v, s};
  }

  REP(Q) {
    int t; cin >> t;
    if (t == 1) {
      int i, x, y, z; cin >> i >> x >> y >> z;
      assert(z == 0);
      P[i] = {y, x};
    }
    else {
      int l, r; cin >> l >> r;
      vector<pair<int,int>> v;
      for (int i = l; i <= r; i++) {
        v.push_back(P[i]);
      }
      sort(all(v));
      bool poss = true;
      vector<ld> intersects;
      for (int i = 0; i < sz(v)-1; i++) {
        if (v[i].first == v[i+1].first && v[i].second != v[i+1].second) {
          // parallel, not possible
          poss = false;
        }
        if (v[i].first != v[i+1].first) {
          FN a(v[i].first, v[i].second);
          FN b(v[i+1].first, v[i+1].second);
          intersects.push_back(a.intersect(b));
        }
      }
      sort(all(intersects));
      if (!poss) {
        cout << 0 << '\n';
      }
      else {
        ld mn = intersects.front();
        ld mx = intersects.back();

        const ld eps = 1e-8;
        if (abs(mx-mn) < eps && mx > 0 && abs(mx-round(mx)) < eps) {
          cout << 1 << '\n';
        }
        else cout << 0 << '\n';
      }
    }
  }
}
