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

// 1: It is always optimal to take a full segment (as many as possible)
// 2: We have four types of segments: 00, 01, 10, 00. It is optimal to remove as
// many segments of types 01/10 from the middle while possible, as this has cost
// 1, but decreases the total number of segments by 2.
// 3: After removing all types of segments, we have a "reduced" segment with no
// 01/10 except possibly at the end.
// 4: The order of deletions/merges does not matter.
// 5: A merge either reduces the number of 00/11, or the number of 01/10. Thus
// the canonical form can be computed just by the # of each type of segment,
// modulo some special cases.

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  vector<int> goleft(n), goright(n);
  for (int i = 0; i < n; i++) {
    if (i == 0 || s[i] == s[i - 1])
      goleft[i] = i;
    else
      goleft[i] = goleft[i - 1];
  }
  for (int i = n - 1; i >= 0; i--) {
    if (i == n - 1 || s[i] == s[i + 1])
      goright[i] = i;
    else
      goright[i] = goright[i + 1];
  }
  map<string, vector<int>> cnt;
  cnt["00"].resize(n);
  cnt["01"].resize(n);
  cnt["10"].resize(n);
  cnt["11"].resize(n);
  auto sum = [&cnt](string s, int l, int r) -> int {
    return cnt[s][r] - (l == 0 ? 0 : cnt[s][l - 1]);
  };
  string cur;
  for (int i = 0; i < n; i++) {
    cur += s[i];
    if (i == n - 1 || s[i] == s[i + 1]) {
      string t = {cur.front(), cur.back()};
      cnt[t][i]++;
      cur.clear();
    }
  }
  for (auto &[_, v] : cnt) {
    for (int i = 1; i < sz(v); i++) {
      v[i] += v[i - 1];
    }
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    l = goleft[l - 1];
    r = goright[r - 1];
    int c00 = sum("00", l, r);
    int c01 = sum("01", l, r);
    int c10 = sum("10", l, r);
    int c11 = sum("11", l, r);

    int cost = c00 + c01 + c10 + c11;

    cost -= min(c00, c11);
    if (c01 == c10 && (c00 == c11 || (c00 > c11 && s[l] == '1') ||
        (c11 > c00 && s[l] == '0'))) {
      cost -= c01 - 1;
    } else {
      cost -= min(c01, c10);
    }

    cout << cost << '\n';
  }
}

