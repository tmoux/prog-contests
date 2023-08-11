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
// }}}

char s[10000];
void solve() {
  int n, k; cin >> n >> k;
  ll x; cin >> x; x--;
  scanf("%s", s);
  //cout << "x = " << x << ", " << s << endl;

  vector<pair<char,int>> v;
  vector<int> u;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    cnt++;
    if (i == n-1 || (s[i] != s[i+1])) {
      v.push_back({s[i], cnt});

      if (s[i] == '*') u.push_back(cnt*k+1);
      cnt = 0;
    }
  }

  vector<int> ans;
  vector<ll> prods(sz(u), x+1);
  for (int i = sz(u)-1; i >= 0; i--) {
    prods[i] = i == sz(u)-1 ? 1LL : u[i+1] * prods[i+1];

    if (i < sz(u)-1 && u[i+1] != 0 && prods[i] / u[i+1] != prods[i+1]) {
      prods[i] = x+1;
      break;
    }
  }
  /*
  for (auto i: prods) {
    cout << i << ' ';
  }
  cout << endl;
  */

  for (ll i: prods) {
    assert(i > 0LL);
    int take = x / i;
    x -= take * i;
    ans.push_back(take);
  }
  //cout << ans << endl;
  assert(x == 0);

  int pt = 0;
  for (auto [c, cnt]: v) {
    if (c == 'a') {
      REP(cnt) {
        cout << 'a';
      }
    }
    else {
      assert(pt < sz(ans));
      int take = ans[pt++];
      REP(take) {
        cout << 'b';
      }
    }
  }
  cout << '\n';
}

int32_t main() {
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
