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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
// }}}

map<pair<int,int>,int> ans;

struct Interval {
  int l, r;
  int id;
};
vector<Interval> intervals;
int n;

bool inside(Interval I, int L, int R) {
  return L <= I.l && I.r <= R && (L != I.l || I.r != R);
}

void recur(int L, int R) {
  if (L > R) return;

  vector<int> prefix(n+2, 0);
  for (auto I: intervals) {
    if (inside(I, L, R)) {
      prefix[I.l] += 1;
      prefix[I.r+1] -= 1;
    }
  }
  int found = -1;
  for (int i = L; i <= R; i++) {
    prefix[i] += prefix[i-1];
    if (prefix[i] == 0) {
      found = i;
      break;
    }
  }

  assert(found != -1);

  ans[{L, R}] = found;

  recur(L, found-1);
  recur(found+1, R);
}

void solve() {
  ans.clear();
  intervals.clear();
  cin >> n;
  intervals.resize(n);
  F0R(i, n) {
    cin >> intervals[i].l >> intervals[i].r;
    intervals[i].id = i;
  }

  recur(1, n);

  F0R(i, n) {
    assert(ans.count({intervals[i].l, intervals[i].r}));
    cout << intervals[i].l << ' ' << intervals[i].r << ' ' << ans[{intervals[i].l, intervals[i].r}] << '\n';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
