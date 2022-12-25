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

const int maxn = 400005, maxk = 20;

int par[maxk][maxn];
ll sum[maxk][maxn];
int cnt = 1;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int Q; cin >> Q;

  F0R(k, maxk) par[k][0] = par[k][1] = -1;
  par[0][1] = 0;

  int last = 0;
  REP(Q) {
    int t;
    ll p, q;
    cin >> t >> p >> q;
    int R = p ^ last;
    ll X = q ^ last;
    // cout << "Query " << t << ' ' << R << ' ' << X << endl;
    if (t == 1) {
      int i = ++cnt;
      if (sum[0][R] >= X) {
        par[0][i] = R;
      }
      else {
        int p = R;
        for (int k = maxk-1; k >= 0; k--) {
          int np = par[k][p];
          if (np >= 1 && sum[0][np] < X) p = np;
        }
        assert(par[0][p] == 0 || sum[0][par[0][p]] >= X);
        par[0][i] = par[0][p];
      }

      // cout << "parent of " << i << " is " << par[0][i] << endl;

      sum[0][i] = X;
      for (int k = 1; k < maxk; k++) {
        if (par[k-1][i] == -1) {
          par[k][i] = -1;
        }
        else {
          par[k][i] = par[k-1][par[k-1][i]];
          sum[k][i] = sum[k-1][i] + sum[k-1][par[k-1][i]];
        }
      }
    }
    else {
      int ans = 0;
      ll curSum = 0;
      for (int k = maxk-1; k >= 0; k--) {
        int nR = par[k][R];
        if (nR >= 0 && curSum + sum[k][R] <= X) {
          curSum += sum[k][R];
          R = nR;
          ans += 1<<k;
        }
      }
      last = ans;
      cout << ans << endl;
    }
  }
}
