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

const int maxn = 5e5+5;
int grundy[maxn];

int mex(vector<int> v) {
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) if (v[i] != i) return i;
  return sz(v);
}

void init() {
  const int B = 500;
  for (int n = 1; n <= B; n++) {
    vector<int> v;
    for (int i = 0; i <= n-2; i++) {
      v.push_back(grundy[i] ^ grundy[n-i-2]);
    }
    grundy[n] = mex(v);
  }
  const int P = 34;
  for (int n = B+1; n < maxn; n++) {
    grundy[n] = grundy[n-P];
  }
}

int solve() {
  int N; cin >> N;
  string s; cin >> s;
  int r = count(all(s), 'R');
  int b = count(all(s), 'B');
  if (r > b) return 1;
  else if (r < b) return 0;
  else {
    int ans = 0;
    int cur = 0;
    for (int i = 0; i < N; i++) {
      cur++;
      if (i + 1 == N || s[i] == s[i+1]) {
        ans ^= grundy[cur];
        cur = 0;
      }
    }
    return ans;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init();
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "Alice" : "Bob") << '\n';
  }
}
