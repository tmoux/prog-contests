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

string s;
int k;
bool poss = true;
void F(int i) {
  if (i < 0) poss = false;
  else {
    bool found = false;
    for (char c = s[i]+1; c < 'a'+k; c++) {
      bool ok = true;
      if (i > 0 && s[i-1] == c) ok = false;
      if (i > 1 && s[i-2] == c) ok = false;
      if (ok) {
        s[i] = c;
        found = true;
        break;
      }
    }
    if (found) return;
    else {
      F(i-1);
      if (!poss) return;
      else {
        for (char c = 'a'; c < 'a'+k; c++) {
          bool ok = true;
          if (i > 0 && s[i-1] == c) ok = false;
          if (i > 1 && s[i-2] == c) ok = false;
          if (ok) {
            s[i] = c;
            found = true;
            break;
          }
        }
      }
      DEBUG(s);
      assert(found);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> s >> k;
  F(s.size()-1);
  DEBUG(poss);
  cout << s << endl;
  return 0;
  auto next = [&](string& s) -> bool {
    bool all = true;
    for (char c: s) if (c != 'a' + k - 1) all = false;
    if (all) return false;

    for (int i = (int)s.size()-1, c = 1; i >= 0; i--) {
      if (c == 0) break;
      if (s[i] < 'a'+k-1) {
        s[i]++;
        break;
      }
      else s[i] = 'a';
    }

    return true;
  };

  auto ok = [&](string& s) -> bool {
    for (int i = 0; i < (int)s.size(); i++) {
      if (i + 1 < (int)s.size() && s[i] == s[i+1]) return false;
      if (i > 0 && i + 1 < (int)s.size() && s[i-1] == s[i+1]) return false;
    }
    return true;
  };

  auto solve = [&]() -> string {
    bool b = next(s);
    if (!b) return "";
    while (!ok(s)) {
      b = next(s);
      if (!b) return "";
    }
    return s;
  };

  cout << solve() << endl;
}
