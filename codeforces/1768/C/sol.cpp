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
  int N; cin >> N;
  vector<int> A(N);
  map<int, vector<int>> occ;
  F0R(i, N) {
    cin >> A[i];
    occ[A[i]].push_back(i);
  }

  vector<int> e1, e2;
  vector<vector<int>> ans(2, vector<int>(N));
  for (int i = N; i >= 1; i--) {
    int s = sz(occ[i]);
    if (s > 2) {
      cout << "NO" << '\n';
      return;
    }
    else if (s == 2) {
      int a = occ[i][0], b = occ[i][1];
      ans[0][a] = i;
      e2.push_back(a);
      ans[1][b] = i;
      e1.push_back(b);
    }
    else if (s == 1) {
      int a = occ[i][0];
      ans[0][a] = ans[1][a] = i;
    }
    else if (s == 0) {
      if (e1.empty()) {
        cout << "NO" << '\n';
        return;
      }
      else {
        int a = e1.back(); e1.pop_back();
        int b = e2.back(); e2.pop_back();
        ans[0][a] = i;
        ans[1][b] = i;
      }
    }
  }
  cout << "YES\n";
  F0R(i, 2) {
    F0R(j, N) {
      cout << ans[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    solve();
  }
}
