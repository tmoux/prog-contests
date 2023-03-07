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
int N;
string S[maxn];
vector<char> v;

int bad[maxn][maxn];

using vi = vector<int>;
void rec(int i, vi& A, vi& B, vi& C) {
  if (i == 18) {
    assert(sz(A) == 6 && sz(B) == 6 && sz(C) == 6);
    for (int j: A) cout << v[j];
    cout << ' ';
    for (int j: B) cout << v[j];
    cout << ' ';
    for (int j: C) cout << v[j];
    cout << '\n';
    exit(0);
  }

  auto can = [&](int j, const vi& vec) {
    for (int k: vec) if (bad[k][j]) return false;
    return true;
  };

  if (sz(A) < 6 && can(i, A)) {
    A.push_back(i);
    rec(i+1, A, B, C);
    A.pop_back();
  }
  if (sz(B) < 6 && can(i, B)) {
    B.push_back(i);
    rec(i+1, A, B, C);
    B.pop_back();
  }
  if (sz(C) < 6 && can(i, C)) {
    C.push_back(i);
    rec(i+1, A, B, C);
    C.pop_back();
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  set<char> s;
  vector<pair<char, char>> edges;
  F0R(i, N) {
    cin >> S[i];
    for (char c: S[i]) {
      s.insert(c);
    }
    edges.emplace_back(S[i][0], S[i][1]);
    edges.emplace_back(S[i][0], S[i][2]);
    edges.emplace_back(S[i][1], S[i][2]);
  }

  if (sz(s) > 18) {
    cout << 0 << '\n';
    return 0;
  }

  for (char c = 'a'; c <= 'z'; c++) {
    if (sz(s) < 18 && !s.count(c)) s.insert(c);
  }

  map<char, int> mp;
  int cnt = 0;
  for (char c: s) {
    v.push_back(c);
    mp[c] = cnt++;
  }

  for (auto [a, b]: edges) {
    int i = mp[a], j = mp[b];
    if (i == j) {
      cout << 0 << '\n';
      return 0;
    }
    bad[i][j] = bad[j][i] = 1;
  }

  vector<int> A, B, C;
  rec(0, A, B, C);

  cout << 0 << '\n';
}
