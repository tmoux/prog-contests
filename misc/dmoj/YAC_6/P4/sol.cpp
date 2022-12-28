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

const int maxn = 105;

int mex(vector<int> v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
  for (int i = 0; i < sz(v); i++) {
    if (v[i] > i) return i;
  }
  return sz(v);
}

int sg[maxn][maxn][maxn][maxn];
int f(int i, int j, int R, int C) {
  int& res = sg[i][j][R][C];
  if (res != -1) return res;
  vector<int> v;
  for (int r = R-1; r >= i; r--)
    v.push_back(f(i, j, r, C));
  for (int d = 1; i-d >= 1; d++)
    v.push_back(f(i-d, j, R-d, C));
  for (int c = C-1; c >= j; c--)
    v.push_back(f(i, j, R, c));
  for (int d = 1; j-d >= 1; d++)
    v.push_back(f(i, j-d, R, C-d));
  for (int ii = i-1; ii >= 1; ii--)
    v.push_back(f(ii, j, R, C));
  for (int jj = j-1; jj >= 1; jj--)
    v.push_back(f(i, jj, R, C));
  for (int d = 1; i-d >= 1 && j-d >= 1; d++)
    v.push_back(f(i-d, j-d, R, C));

  return res = mex(v);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(sg, -1, sizeof sg);

  cout << "{";
  for (int i = 0; i <= 100; i++) {
    if (i > 0) cout << ", ";
    cout << f(i, i, i, i);
  }
  cout << "}\n";
  return 0;

  int N, M; cin >> N >> M;
  vector<int> S(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i];
  }

  sort(all(S));
  if (M == 1 && S.front() == S.back()) {
    // subtask 2
    if (N % 2 == 0 || S[0] == 1) {
      cout << 1 << '\n';
    }
    else cout << -1 << '\n';
  }
  else {
    int x = 0;
    for (auto i: S) x ^= f(i, i, i, i);
    for (int i = 1; i <= M; i++) {
      if (f(i, i, i, i) == x) {
        cout << i << '\n';
        return 0;
      }
    }
    cout << -1 << '\n';
  }
}
