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

int solve() {
  string S; cin >> S;
  int N = S.size();
  vector<vector<int>> char_count(26, vector<int>(N, 0));
  F0R(i, N) {
    for (char c = 'a'; c <= 'z'; c++) {
      char_count[c-'a'][i] = c == S[i] ? 1 : 0;
      if (i > 0) char_count[c-'a'][i] += char_count[c-'a'][i-1];
    }
  }

  auto get_count = [&](char c, int l, int r) -> int {
    return l == 0 ? char_count[c-'a'][r] : char_count[c-'a'][r] - char_count[c-'a'][l-1];
  };

  int ans = 0;
  int Q; cin >> Q;
  REP(Q) {
    int L, R; cin >> L >> R;
    L--; R--;
    map<char, int> mp;
    int num_odd = 0;
    for (char c = 'a'; c <= 'z'; c++) {
      mp[c] += get_count(c, L, R);
      if (mp[c] % 2 == 1) num_odd++;
    }

    auto check = [&](int l, int r) -> bool {
      for (char c = 'a'; c <= 'z'; c++) {
        if (get_count(c, l, r) != mp[c]/2) return false;
      }
      return true;
    };

    bool poss = num_odd == 1;
    if (poss) {
      int len = (R-L+1)/2;
      poss = check(L, L+len-1) || check(R-len+1, R);
    }

    if (poss) ans++;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
