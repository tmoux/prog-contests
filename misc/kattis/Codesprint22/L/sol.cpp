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

const int maxn = 1005;
int N, M;
string S[maxn];

int z[maxn*maxn+maxn];
void z_function(string s) {
  int n = (int) s.length();
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
}

int longest[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  F0R(i, M) {
    cin >> S[i];
  }
  string match;
  FOR(i, 1, M) {
    if (i > 1) match += '#';
    match += S[i];
  }
  F0R(i, N) {
    string t = S[0].substr(i);
    string tt = t+"$"+match;
    continue;
    z_function(tt);
    cout << i << endl;
    continue;
    for (int j = sz(t); j < sz(tt); j++) {
      ckmax(longest[i], z[j]);
    }
  }
  for (int i = 1; i < M; i++) {

  }

  /*
  if (check(N)) {
    int lo = 0, hi = N;
    while (lo + 1 < hi) {
      int mid = (lo+hi)/2;
      if (check(mid)) {
        hi = mid;
      }
      else lo = mid;
    }
    cout << hi << '\n';
  }
  else {
    cout << -1 << '\n';
  }
  */
}
