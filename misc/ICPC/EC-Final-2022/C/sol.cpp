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

ll ex10[20];
vector<int> dx;
ll dp[20][2][20];

const ll INF = LLONG_MAX;

ll f(int i, int c, int k) {
  if (i == 18) {
    return k == 0 ? 0 : INF;
  }
  auto& res = dp[i][c][k];
  if (res != -1) return res;
  int d = dx[i] + c;
  res = INF;
  if (d == 10) {
    if (k > 0) res = f(i+1, 1, k-1);
  }
  else {
    res = f(i+1, 0, k);
    if (k > 0) {
      ll tr = f(i+1, 1, k-1);
      if (d > 0 && tr < INF) ckmin(res, tr + (10 - d) * ex10[i]);
    }
  }
  return res;
}

void solve() {
  memset(dp, -1, sizeof dp);
  ll x; cin >> x;
  ll k; cin >> k;

  if (k == 0) {
    dx.clear();
    while (x > 0) {
      dx.push_back(x % 10);
      x /= 10;
    }
    while (sz(dx) < 19) dx.push_back(0);
    for (int i = 0; i <= 18; i++) {
      if (dx[i] < 9) {
        cout << ex10[i] << '\n';
        return;
      }
    }
    assert(false);
  }
  else {
    dx.clear();
    while (x > 0) {
      dx.push_back(x % 10);
      x /= 10;
    }
    ll div = 0;
    reverse(all(dx));
    while (dx.back() == 0) {
      dx.pop_back();
      div++;
    }
    reverse(all(dx));
    while (sz(dx) < 19) dx.push_back(0);

    // cout << dx << endl;
    ll ans = f(0, 0, k);
    if (ans < INF) {
      string ret;
      while (ans > 0) {
        ret += (ans % 10) + '0';
        ans /= 10;
      }
      reverse(all(ret));
      REP(div) ret += '0';
      cout << ret << '\n';
    }
    else {
      cout << -1 << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ex10[0] = 1;
  for (int i = 1; i <= 18; i++) {
    ex10[i] = ex10[i-1] * 10;
  }
  int T; cin >> T;
  while (T--) solve();
}
