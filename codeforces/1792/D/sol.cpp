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

namespace Trie {
  const int C = 10;
  struct Node {
    Node *ch[C];
    Node() {
      F0R(i, C) ch[i] = nullptr;
    }
  };

  const int MX = 5e5+5;
  Node nodes[MX];
  int cur = 0;
  Node* reset() {
    cur = 0;
    nodes[cur] = Node();
    return &nodes[cur];
  }

  Node* newNode() {
    nodes[++cur] = Node();
    return &nodes[cur];
  }

  void insert(Node *root, vector<int> v) {
    F0R(i, sz(v)) {
      if (!root->ch[v[i]]) root->ch[v[i]] = newNode();
      root = root->ch[v[i]];
    }
  }

  int max_depth(Node *root, vector<int> v) {
    int d = 0;
    F0R(i, sz(v)) {
      if (!root->ch[v[i]]) break;
      else root = root->ch[v[i]], d++;
    }
    return d;
  }
};


void solve() {
  int N, M; cin >> N >> M;
  vector<vector<int>> P(N, vector<int>(M));
  Trie::Node* root = Trie::reset();
  F0R(i, N) {
    vector<int> pos(M);
    F0R(j, M) {
      cin >> P[i][j]; --P[i][j];
      pos[P[i][j]] = j;
    }
    Trie::insert(root, pos);
  }

  F0R(i, N) {
    int ans = Trie::max_depth(root, P[i]);
    cout << ans << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
