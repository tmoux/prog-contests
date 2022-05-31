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

char switch_case(char c) {
  if ('a' <= c && c <= 'z') {
    return c-'a'+'A';
  }
  else {
    return c-'A'+'a';
  }
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s;
  cin >> s;
  string t; cin >> t;
  map<char, int> cnt;
  for (char c: s) cnt[c]++;
  map<char, int> cnt2;
  for (char c: t) cnt2[c]++;
  int A = 0, B = 0;
  for (char c = 'a'; c <= 'z'; c++) {
    int a1 = cnt2[c];
    int a2 = cnt2[switch_case(c)];

    int b1 = cnt[c];
    int b2 = cnt[switch_case(c)];

    int k = min(a1, b1);
    a1 -= k;
    b1 -= k;
    A += k;

    k = min(a2, b2);
    a2 -= k;
    b2 -= k;
    A += k;

    B += min(a1+a2, b1+b2);
  }
  cout << A << ' ' << B << endl;
}

