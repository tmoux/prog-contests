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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  vector<int> P(N+1);
  FOR(i, 1, N+1) cin >> P[i];

  int CYC = 0;
  vector<int> cycSize(N+1);
  vector<int> toId(N+1, -1);
  vector<int> prev(N+1);

  auto dfs = y_combinator([&](auto dfs, int i, int c) -> void {
    if (toId[i] != -1) return;
    toId[i] = c;
    cycSize[c]++;
    prev[P[i]] = i;
    dfs(P[i], c);
  });

  for (int i = 1; i <= N; i++) {
    if (toId[i] == -1) {
      dfs(i, CYC);
      CYC++;
    }
  }

  // cout << cycSize << endl;
  // cout << toId << endl;

  auto query = [&](const set<int>& s) -> int {
    map<int, int> cycCount;
    map<int, int> adjacent;
    for (int i: s) {
      cycCount[toId[i]]++;
      if (s.count(prev[i])) adjacent[toId[i]]++;
    }

    int comps = CYC - sz(cycCount);
    for (auto [c, cnt]: cycCount) {
      int add = cnt - adjacent[c];
      comps += add;
    }
    return comps;
  };

  while (Q--) {
    int k; cin >> k;
    set<int> s;
    REP(k) {
      int x; cin >> x;
      s.insert(x);
    }

    cout << query(s) << '\n';
  }
}
