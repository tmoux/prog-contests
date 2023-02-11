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

pair<char, char> others(char c) {
  if (c == 'w') return {'i', 'n'};
  if (c == 'i') return {'w', 'n'};
  if (c == 'n') return {'w', 'i'};
  assert(false);
}

char other(char c, char d) {
  if ('w' != c && 'w' != d) return 'w';
  if ('i' != c && 'i' != d) return 'i';
  if ('n' != c && 'n' != d) return 'n';
  assert(false);
}

void solve() {
  int M; cin >> M;
  map<char, map<char, vector<int>>> adj;
  auto getsz = [&](char a, char b) {
    return sz(adj[a][b]);
  };
  auto pop = [&](char a, char b) {
    auto i = adj[a][b].back();
    adj[a][b].pop_back();
    return i;
  };
  vector<string> v(M);
  F0R(i, M) {
    cin >> v[i];
    map<char, int> mp;
    for (char c: v[i]) mp[c]++;
    if (sz(mp) == 1) {
      char c = mp.begin()->first;
      auto [d, e] = others(c);
      adj[c][d].push_back(i);
      adj[c][e].push_back(i);
    }
    else if (sz(mp) == 2) {
      char c = mp.begin()->first;
      char d = next(mp.begin())->first;
      if (mp.begin()->second == 1) swap(c, d);
      auto e = other(c, d);
      adj[c][e].push_back(i);
    }
  }

  vector<tuple<int, char, int, char>> ans;

  while (getsz('w', 'i') && getsz('i', 'w')) {
    auto i1 = pop('w', 'i');
    auto i2 = pop('i', 'w');
    ans.emplace_back(i1, 'w', i2, 'i');
  }
  while (getsz('i', 'n') && getsz('n', 'i')) {
    auto i1 = pop('i', 'n');
    auto i2 = pop('n', 'i');
    ans.emplace_back(i1, 'i', i2, 'n');
  }
  while (getsz('n', 'w') && getsz('w', 'n')) {
    auto i1 = pop('n', 'w');
    auto i2 = pop('w', 'n');
    ans.emplace_back(i1, 'n', i2, 'w');
  }

  while (true) {
    int wi = getsz('w', 'i');
    int in = getsz('i', 'n');
    int nw = getsz('n', 'w');

    int iw = getsz('i', 'w');
    int ni = getsz('n', 'i');
    int wn = getsz('w', 'n');

    bool done = true;

    if (wi >= 1 && in >= 1 && nw >= 1) {
      auto i1 = pop('w', 'i');
      auto i2 = pop('i', 'n');
      auto i3 = pop('n', 'w');
      ans.push_back({i1, 'w', i2, 'i'});
      ans.push_back({i2, 'w', i3, 'n'});
      done = false;
    }

    if (iw >= 1 && ni >= 1 && wn >= 1) {
      auto i1 = pop('i', 'w');
      auto i2 = pop('w', 'n');
      auto i3 = pop('n', 'i');
      ans.push_back({i1, 'i', i2, 'w'});
      ans.push_back({i2, 'i', i3, 'n'});
      done = false;
    }

    if (done) break;
  }

  cout << sz(ans) << '\n';
  for (auto [i1, c1, i2, c2]: ans) {
    cout << i1+1 << ' ' << c1 << ' ' << i2+1 << ' ' << c2 << '\n';
  }

  /*
  pair<int, int> ans = {2e9, -1};
  for (int cycles = 0; cycles <= 2*M; cycles++) {
    int wi = getsz('w', 'i');
    int in = getsz('i', 'n');
    int nw = getsz('n', 'w');

    int iw = getsz('i', 'w');
    int ni = getsz('n', 'i');
    int wn = getsz('w', 'n');
    if (min({wi, in, nw}) >= cycles) {
      if (wi-cycles == iw &&
          in-cycles == ni &&
          nw-cycles == wn) {
        int tr = 2 * cycles + 2 * (iw + ni + wn);
        cout << cycles << ": " << tr << endl;
      }
    }
  }
  */
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
