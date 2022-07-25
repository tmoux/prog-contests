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

const int maxn = 1e5+5;
int N;
ll A[maxn];

const int maxk = 70;
ll dp[maxk];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
  }
  dp[0] = 1;
  for (int i = 2; i <= N; i++) {
    vector<pair<ll, ll>> gaps = {{A[i]-A[i-1]-1, 1}};
    ll cur = 1;
    vector<ll> ndp(maxk, 0);
    for (int iter = 0; ; iter++) {
      cout << iter << ": " << gaps << endl;
      DEBUG(cur);
      for (int j = 0; j <= iter; j++) {
        ckmax(ndp[iter], cur + dp[j]);
      }

      if (gaps.empty()) break;
      map<ll, ll> cnt;
      ll ncur = 0;
      for (auto [g, c]: gaps) {
        g--;
        ll g1 = g/2;
        ll g2 = g-g/2;
        ncur += c;
        if (g1 > 0) {
          cnt[g1] += c;
        }
        if (g2 > 0) {
          cnt[g2++] += c;
        }
      }
      cur = ncur;

      gaps.clear();
      for (auto [g, c]: cnt) {
        gaps.push_back({g, c}); 
      }
    }

    F0R(j, maxk) {
      dp[j] = ndp[j];
      if (dp[j] != 0) {
        cout << j << ": " << dp[j] << endl;
      }
    }
  }

  ll ans = 0;
  F0R(i, maxk) {
    ckmax(ans, dp[i]);
  }
  cout << ans << '\n';
}
