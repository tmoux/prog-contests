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

#define pb push_back
#define f first
#define s second

const int MX = 2e5+5;
int B;
using vpi = vector<pair<int, int>>;

// hash checked
int N, M;
vector<vpi> graph(MX); // {ed, edNum}
vector<vpi::iterator> its(MX);
vector<bool> used(MX);

vpi eulerPath(int r) {
  F0R(i, N) its[i] = begin(graph[i]);
  F0R(i, M) used[i] = false;
  vpi ans, s{{r, -1}};
  int lst = -1;
  while (sz(s)) {
    int x = s.back().f; auto &it = its[x], en = end(graph[x]);
    while (it != en && used[it->s]) it++;

    if (it == en) {
      if (lst != -1 && lst != x) return {};
      ans.pb(s.back()); s.pop_back(); if (sz(s)) lst = s.back().f;
    } else {
      s.pb(*it);
      used[it->s] = 1;
    }
  }
  if (sz(ans) != M+1) return {};
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m; cin >> n >> m;
  cin >> B;
  vector<string> v(n);

  vpi edges;
  bool poss = true;
  F0R(i, n) {
    cin >> v[i];

    int j = 0;
    while (j < sz(v[i]) && v[i][j] != '1') j++;
    if (j == sz(v[i])) {
      assert(false);
    }
    else {
      int start = j;
      for (int idx = j; idx < sz(v[i]); idx += m) {
        if (v[i][idx] != '1') {
          poss = false;
        }
        for (int k = 1; k < B && idx+k < sz(v[i]); k++) {
          if (v[i][idx+k] != '0') {
            poss = false;
          }
        }
      }
      int j = sz(v[i])-1;
      while (j >= 0 && v[i][j] != '1') j--;
      int end = (m-(sz(v[i])-1-j)-1);
      edges.push_back({start, end});

      if (!poss) break;
    }
  }

  if (!poss) {
    cout << -1 << '\n';
    return 0;
  }

  N = m;
  M = sz(edges);
  for (int i = 0; i < sz(edges); i++) {
    auto [a, b] = edges[i];
    graph[a].push_back({b, i+1});
  }
  // cout << edges << endl;
  int start = B-1;
  auto euler = eulerPath(start);
  if (euler.empty()) {
    cout << -1 << '\n';
  }
  vector<int> ans;
  // cout << euler << endl;
  for (auto [_, id]: euler) {
    if (id != -1) ans.push_back(id);
  }
  reverse(all(ans));
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << '\n';
}
