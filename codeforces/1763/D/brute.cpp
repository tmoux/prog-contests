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

int solve() {
  int N, i, j, x, y;
  cin >> N >> i >> j >> x >> y;
  /*
  if (x > y) {
    swap(x, y);
    i = N + 1 - i;
    j = N + 1 - j;
    swap(i, j);
  }
  */

  vector<int> perm(N);
  iota(all(perm), 1);

  int ans = 0;
  map<int, int> cnt;
  do {
    int idx = -1;
    F0R(i, N) if (perm[i] == N) {
      idx = i;
      break;
    }
    bool p = idx != 0 && idx != N-1;
    for (int j = idx-1; j >= 0; j--) {
      if (perm[j] > perm[j+1]) {
        p = false;
        break;
      }
    }
    for (int j = idx+1; j < N; j++) {
      if (perm[j] > perm[j-1]) {
        p = false;
        break;
      }
    }

    if (p && perm[i-1] == x && perm[j-1] == y) {
      cnt[idx+1]++;
      ans++;
    }
  } while (next_permutation(all(perm)));
  //cout << cnt << endl;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << endl;
  }
}
