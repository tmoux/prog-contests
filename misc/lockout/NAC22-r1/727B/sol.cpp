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

bool check(char c) {
  return ('0' <= c && c <= '9') || c == '.';
}
int ctoi(char c) {
  return c - '0';
}

vector<int> digits(int x) {
  vector<int> r;
  while (x) {
    r.push_back(x % 10);
    x /= 10;
  }
  if (r.empty()) {
    return {0};
  }
  else return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;

  int total = 0, dec = 0;

  auto parse_dig = [&](string s) {
    string t = s;
    if (sz(s) >= 3 && s[sz(s)-3] == '.') {
      t = s.substr(0, sz(s)-3);
      dec += ctoi(s[sz(s)-2])*10 + ctoi(s.back());
    }
    int mult = 1;
    for (int i = sz(t)-1; i >= 0; i -= 4) {
      total += ctoi(t[i]) * mult;
      if (i-1 >= 0) total += ctoi(t[i-1]) * mult * 10;
      if (i-2 >= 0) total += ctoi(t[i-2]) * mult * 100;

      mult *= 1000;
    }
  };
  vector<string> vs;
  string cur;
  F0R(i, sz(s)) {
    if (check(s[i])) {
      cur += s[i];
      if (i+1 == sz(s) || !check(s[i+1])) {
        vs.push_back(cur);
      }
    }
    else cur.clear();
  }
  for (auto s: vs) {
    parse_dig(s);
    // cout << total << ' ' << dec << endl;
  }
  if (dec % 100 == 0) {
    total += dec/100;
    auto d = digits(total);
    string s;
    for (int i = 0; i < sz(d); i += 3) {
      s += d[i]+'0';
      if (i+1 < sz(d)) s += d[i+1]+'0';
      if (i+2 < sz(d)) s += d[i+2]+'0';

      if (i+3 < sz(d)) s += '.';
    }
    reverse(all(s));
    cout << s << endl;
  }
  else {
    total += dec/100;
    dec = dec % 100;

    auto d = digits(total);
    string s;
    for (int i = 0; i < sz(d); i += 3) {
      s += d[i]+'0';
      if (i+1 < sz(d)) s += d[i+1]+'0';
      if (i+2 < sz(d)) s += d[i+2]+'0';

      if (i+3 < sz(d)) s += '.';
    }
    reverse(all(s));
    cout << s;
    if (dec >= 10) cout << '.' << dec << endl;
    else cout << '.' << 0 << dec << endl;
  }
}
