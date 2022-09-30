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

bool solve() {
  string s; cin >> s;
  int N = sz(s);
  assert(N % 2 == 0);
  int num_open = count(all(s), '(');
  int num_need_open = N/2-num_open;

  vector<int> prefix(N), is_ques(N), is_ques_open(N);
  int num_open_seen = 0;
  F0R(i, N) {
    char c;
    if (s[i] == '?') {
      is_ques[i] = 1;
      if (num_open_seen < num_need_open) {
        c = '(';
        num_open_seen++;
        is_ques_open[i] = 1;
      }
      else c = ')';
    }
    else c = s[i];

    prefix[i] = c == '(' ? 1 : -1;
    if (i > 0) prefix[i] += prefix[i-1];
  }

  int mn = 0;
  F0Rd(i, N) {
    ckmin(mn, prefix[i]);
    if (is_ques[i]) {
      if (is_ques_open[i]) {
        if (mn >= 2) return false;
      }
      else {
        mn = 1e9;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "YES" : "NO") << '\n';
  }
}
