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
bool is_square[maxn];

bool check(vector<int> p) {
  F0R(i, sz(p)) {
    if (!is_square[i + p[i]]) return false;
  }
  return true;
}

vector<int> squares;

int N;
vector<int> st;
vector<int> ans;
bool vis[maxn];

void dfs(int i) {
  if (!ans.empty()) return;
  if (vis[i]) {
    return;
  }
  vis[i] = true;
  if (i == N) {
    ans = st;
    return;
  }
  for (int sq: squares) {
    if (i+i <= sq) {
      int len = (sq - i) - (i-1);
      if (i+len <= N) {
        st.push_back(len);
        dfs(i+len);
        st.pop_back();
      }
    }
  }
}

void solve() {
  cin >> N;
  st.clear();
  ans.clear();
  for (int i = 0; i <= N; i++) vis[i] = false;

  dfs(0);

  if (ans.empty()) {
    cout << -1 << '\n';
  }
  else {
    int c = 0;
    for (auto x: ans) {
      F0Rd(i, x) {
        cout << c+i << ' ';
      }
      c += x;
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int i = 0; i*i <= 200000; i++) squares.push_back(i*i);
  int T; cin >> T;
  while (T--) {
    solve();
  }
  /*
  for (int i = 0; i <= 100; i++) is_square[i*i] = true;
  int N; cin >> N;

  vector<int> p(N);
  iota(all(p), 0);
  do {
    if (check(p)) {
      cout << p << '\n';
      F0R(i, sz(p)) {
        cout << i+p[i] << ' ';
      }
      cout << '\n';
      exit(0);
    }
  } while (next_permutation(all(p)));
  */
}
