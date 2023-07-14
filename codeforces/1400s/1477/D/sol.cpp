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

int check(vector<int>& p, vector<int>& q, vector<array<int, 2>>& V, bool debug = false) {
  bool poss = true;
  for (auto [l, r]: V) {
    int a = p[l] - p[r];
    int b = q[l] - q[r];
    // if (debug) {
    //   cout << l << ' ' << r << ": " << a << ' ' << b << endl;
    // }
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
      poss = false;
      break;
    }
  }
  if (!poss) return -1;
  int score = 0;
  F0R(i, sz(p)) {
    if (p[i] != q[i]) score++;
  }
  return score;
}

int C = 0;
pair<int, pair<vector<int>, vector<int>>> brute(int N, int M, vector<array<int, 2>> V) {
  pair<int, pair<vector<int>, vector<int>>> ans = {0, {}};
  vector<int> p(N); iota(all(p), 0);
  do {
    vector<int> q(N); iota(all(q), 0);

    do {
      C++;
      int score = check(p, q, V);
      ckmax(ans, {score, {p, q}});
    } while (next_permutation(all(q)));
  } while (next_permutation(all(p)));
  return ans;
}

pair<int, vector<int>> brute2(int N, int M, vector<array<int, 2>> V) {
  pair<int, vector<int>> ans = {-1, {}};
  vector<int> p(N); iota(all(p), 0);
  vector<int> q(N); iota(all(q), 0);

  do {
    int score = check(p, q, V);
    ckmax(ans, {score, q});
  } while (next_permutation(all(q)));
  return ans;
}

void solve() {
  int N, M; cin >> N >> M;
  vector<array<int, 2>> V(M);
  F0R(i, M) {
    cin >> V[i][0] >> V[i][1];
    V[i][0]--, V[i][1]--;
  }

  // cout << brute2(N, M, V) << endl;
  auto [a, pp] = brute(N, M, V);
  auto [p, q] = pp;
  auto [b, vec] = brute2(N, M, V);
  // assert(a == b);
  // assert(a == N);
  DEBUG(N);
  cout << a << ' ' << b << endl;
  cout << p << endl;
  cout << q << endl;

  // cout << brute(N, M, V) << ' ' << brute2(N, M, V) << '\n';
  // DEBUG(C);

  // vector<int> p(N); iota(all(p), 0);
  // cout << check(p, vec, V, true) << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
