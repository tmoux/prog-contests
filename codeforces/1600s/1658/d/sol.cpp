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

int solve() {
  int l, r; cin >> l >> r;
  const int maxk = 19;
  vector<array<int, 2>> cnt(maxk);
  FOR(i, l, r+1) {
    F0R(k, maxk) {
      bool b = i & (1<<k);
      cnt[k][b]++;
    }
  }
  vector<array<int, 2>> cnta(maxk);
  vector<int> a(r-l+1);
  F0R(i, r-l+1) {
    cin >> a[i];
    F0R(k, maxk) {
      bool b = a[i] & (1<<k);
      cnta[k][b]++;
    }
  }
  int x = 0;
  cout << cnt[0][0] << ' ' << cnt[0][1] << endl;
  cout << cnta[0][0] << ' ' << cnta[0][1] << endl;
  F0R(k, maxk) {
    if (cnt[k][0] == cnta[k][0] && cnt[k][1] == cnta[k][1]) {

    }
    else {
      assert(cnt[k][0] == cnta[k][1] && cnt[k][1] == cnta[k][0]);
      x |= 1<<k;
    }
  }

  vector<int> b(r-l+1);
  F0R(i, r-l+1) b[i] = a[i] ^ x;
  sort(all(b));
  // cout << b << endl;
  // cout << "x = " << x << endl;
  F0R(i, r-l+1) {
    // cout << "check " << b[i] << ' ' << l+i << endl;
    assert(b[i] == l+i);
  };
  return x;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int ans = solve();
  }
}
