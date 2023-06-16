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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  int K; cin >> K;
  vector<vector<int>> G(18, vector<int>(18));
  F0R(i, N) {
    int r, c, s; cin >> r >> c >> s;
    r--, c--;
    G[r][c] = s;
  }

  int ans = N;
  F0R(mask, 1 << 18) {
    int num = 0;
    int sum = 0;
    F0R(i, 18) {
      if (mask & (1 << i)) {
        num++;
        F0R(j, 18) {
          sum += G[i][j];
        }
      }
    }

    vector<int> cols;
    F0R(j, 18) {
      int t = 0;
      F0R(i, 18) {
        if (!(mask & (1 << i))) {
          t += G[i][j];
        }
      }
      cols.push_back(t);
    }
    sort(all(cols), greater());

    F0R(i, sz(cols)) {
      if (sum >= K) break;
      else {
        num++;
        sum += cols[i];
      }
    }

    ckmin(ans, num);
  }
  cout << ans << '\n';
}
