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

ll solve() {
  int N; cin >> N;
  string s; cin >> s;
  vector<ll> dp(N);
  vector<int> len(N);
  auto pal = [&](int i, int j) {
      if ((j-i+1) % 2 != 0) return false;
      while (i < j) {
          if (s[i] != s[j]) return false;
          i++, j--;
      }
      return true;
  };
  F0Rd(i, N) {
      if (i + 1 < N && s[i] == s[i+1]) len[i] = 2;
      else if (i + 1 < N && i+len[i+1]+1 < N && s[i] == s[i+len[i+1]+1]) {
          len[i] = len[i+1] + 2;
      }
  }

  // F0R(i, N) {
  //     cout << len[i] << ' ';
  // }
  // cout << endl;

  ll ans = 0;
  vector<vector<int>> is(N, vector<int>(N));
  F0Rd(i, N) {
      for (int j = i+1; j < N; j += 2) {
          if (pal(i, j)) is[i][j] = 1;
          else {
              for (int k = i+1; k < j; k += 2) {
                  if (pal(i, k) && is[k+1][j]) is[i][j] = 1;
              }
          }
          if (is[i][j]) ans++;
      }
      // if (len[i] > 0) is[i][i+len[i]-1] = 1;
      // FOR(j, i, N) {
      //     if (len[i] > 0 && i+len[i] < N && is[i+len[i]][j]) {
      //         is[i][j] = 1;
      //     }
      //     if (is[i][j]) ans++;
      // }
  }

  F0R(i, N) {
      FOR(j, i, N) {
          // cout << i << ' ' << j << ": " << is[i][j] << endl;
      }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
