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
  vector<string> A(3);
  F0R(i, 3) {
    cin >> A[i];
  }
  vector<array<int, 2>> cnt(3);
  vector<int> maj;
  F0R(i, 3) {
    cnt[i][0] = count(all(A[i]), '0');
    cnt[i][1] = count(all(A[i]), '1');
    maj.push_back(cnt[i][0] >= cnt[i][1] ? 0 : 1);
  }

  auto F = [&](string s, string t, char c) {
    int c1 = count(all(s), c);
    int c2 = count(all(t), c);
    // cout << "strings " << s << ' ' << t << ' ' << c << endl;
    if (c1 < c2) swap(s, t);
    int j = 0;
    for (char ch: s) {
      if (ch != c) {
        cout << ch;
      }
      else {
        while (j < sz(t) && t[j] != c) {
          cout << t[j++];
        }
        j++;
        cout << ch;
      }
    }
    while (j < sz(t)) {
      if (t[j] != c) cout << t[j];
      j++;
    }
    cout << '\n';
  };

  if (maj[0] == maj[1]) {
    F(A[0], A[1], maj[0] + '0');
  }
  else if (maj[1] == maj[2]) {
    F(A[1], A[2], maj[1] + '0');
  }
  else if (maj[0] == maj[2]) {
    F(A[0], A[2], maj[0] + '0');
  }
  else assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
