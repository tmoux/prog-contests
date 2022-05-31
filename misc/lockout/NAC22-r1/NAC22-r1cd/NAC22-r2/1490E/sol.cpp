#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
  template <class Fun>
    class y_combinator_result {
      Fun fun_;

      public:
      template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

      template <class... Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template <class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
!is_same<T_container, string>::value,
  typename T_container::value_type>::type>
  ostream &operator<<(ostream &os, const T_container &v) {
    os << '[';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << ']';
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

void solve() {
  int n; cin >> n;
  vector<pair<ll,int>> a(n);
  F0R(i, n) {
    int x; cin >> x;
    a[i] = {x, i};
  }
  sort(all(a));

  vector<ll> pre(n);
  pre[0] = a[0].first;
  FOR(i, 1, n) pre[i] = pre[i-1] + a[i].first;

  if (n == 1) {
    cout << 1 << '\n';
    cout << 1 << '\n';
    return;
  }
  else {
    vector<int> ans;
    int pt = 0;
    ll sum = 0;
    F0R(i, n) {
      if (pt == i) {
        sum += a[pt].first;
        pt++;
      }
      while (pt < n && a[pt].first <= sum) {
        sum += a[pt].first;
        pt++;
      }
      if ((pt == n) || 
          (i < n-1 && sum > a[n-1].first) ||
          (i == n-1 && sum > a[n-2].first)) {
        ans.push_back(a[i].second);
      }
    }
    sort(all(ans));
    cout << sz(ans) << '\n';
    for (auto i: ans) {
      cout << i+1 << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
