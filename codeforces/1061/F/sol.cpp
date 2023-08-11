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

int N, K;
int depth = 0;

bool ask(int a, int b, int c) {
  cout << "? " << a << ' ' << b << ' ' << c << endl;
  string s; cin >> s;
  return s == "Yes";
}

bool isLeaf(int b) {
  int a = b == 1 ? 2 : 1;
  for (int c = 1; c <= N; c++) {
    if (c == a || c == b) continue;
    if (ask(a, b, c)) return false;
  }
  return true;
}

int findLeaf() {
  while (1) {
    int i = rng() % N + 1;
    if (isLeaf(i)) return i;
  }
}

vector<int> findPaths(int a, int b) {
  vector<int> v;
  for (int i = 1; i <= N; i++) {
    if (i == a || i == b) continue;
    if (ask(a, i, b)) v.push_back(i);
  }
  return v;
}

bool isRoot(int i, int a, int b, vector<int> v) {
  int ca = 0, cb = 0;
  for (int j: v) {
    if (j == i) continue;
    (ask(i, j, a) ? ca : cb)++;
  }
  return ca == cb;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  int cnt = 1, level = 1;
  while (cnt < N) {
    level *= K;
    cnt += level;
    depth++;
  }

  int a = findLeaf();
  int b = -1;
  vector<int> v;
  while (1) {
    b = findLeaf();
    v = findPaths(a, b);
    if (sz(v) == 2*depth-1) {
      break;
    }
  }

  for (auto i: v) {
    if (isRoot(i, a, b, v)) {
      cout << "! " << i << endl;
      return 0;
    }
  }
}
