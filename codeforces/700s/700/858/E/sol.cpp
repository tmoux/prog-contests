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

string gensym() {
  string s;
  REP(6) {
    int r = rng () % 36;
    if (r < 26) s += r + 'a';
    else s += (r - 26) + '0';
  }
  return s;
}

bool isnum(string s) {
  if (s[0] == '0') return 0; // disallow leading 0's
  for (char c: s) if (!isdigit(c)) return 0;
  return 1;
}

int main() {
  int N; cin >> N;
  vector<pair<string, int>> v(N);
  int M = 0;
  F0R(i, N) {
    cin >> v[i].first >> v[i].second;
    if (v[i].second == 1) M++;
  }

  set<int> open1, open0;
  set<string> other1, other0;
  set<int> b1, b0;
  for (int i = 1; i <= M; i++) open1.insert(i);
  for (int i = M+1; i <= N; i++) open0.insert(i);
  F0R(i, N) {
    if (isnum(v[i].first) && stoi(v[i].first) <= N) {
      int d = stoi(v[i].first);
      (d <= M ? open1 : open0).erase(d);
      if (v[i].second == 1 && d > M) {
        b1.insert(d);
      }
      else if (v[i].second == 0 && d <= M) {
        b0.insert(d);
      }
    }
    else if (v[i].second == 1) {
      other1.insert(v[i].first);
    }
    else other0.insert(v[i].first);
  }

  // cout << open1 << ' ' << open0 << endl;
  // cout << other1 << ' ' << other0 << endl;
  // cout << b1 << ' ' << b0 << endl;

  vector<pair<string, string>> ans;
  if (open1.empty() && open0.empty()) {
    if (!b1.empty()) {
      auto s = *b1.begin(); b1.erase(b1.begin());
      string t = gensym();
      ans.emplace_back(to_string(s), t);
      other1.insert(t);
      open0.insert(s);
    }
  }

  while (1) {
    if (b1.empty() && b0.empty()) break;
    if (!open1.empty() && !b1.empty()) {
      int i = *open1.begin(); open1.erase(open1.begin());
      int j = *b1.begin(); b1.erase(b1.begin());
      ans.emplace_back(to_string(j), to_string(i));
      open0.insert(j);
    }
    else if (!open0.empty() && !b0.empty()) {
      int i = *open0.begin(); open0.erase(open0.begin());
      int j = *b0.begin(); b0.erase(b0.begin());
      ans.emplace_back(to_string(j), to_string(i));
      open1.insert(j);
    }
    else break;
  }
  assert(b1.empty() && b0.empty());
  for (auto s: other1) {
    int i = *open1.begin(); open1.erase(open1.begin());
    ans.emplace_back(s, to_string(i));
  }
  for (auto s: other0) {
    int i = *open0.begin(); open0.erase(open0.begin());
    ans.emplace_back(s, to_string(i));
  }

  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << "move " << a << ' ' << b << '\n';
  }
}
