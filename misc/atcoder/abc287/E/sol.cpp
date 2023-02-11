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
  struct Node {
    int cnt = 0;
    Node *ch[26];
    Node() {
      F0R(i, 26) ch[i] = nullptr;
    }
  };

  const int MX = 1e6+6;
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

  void insert(Node *root, const string& s) {
    F0R(i, sz(s)) {
      int c = s[i] - 'a';
      if (!root->ch[c]) root->ch[c] = newNode();
      root = root->ch[c];
      root->cnt++;
    }
  }

  void remove(Node *root, const string& s) {
    F0R(i, sz(s)) {
      int c = s[i] - 'a';
      root = root->ch[c];
      root->cnt--;
    }
  }

  int lcp(Node *root, const string& s) {
    int ans = 0;
    F0R(i, sz(s)) {
      int c = s[i] - 'a';
      root = root->ch[c];
      if (root->cnt == 0) break;
      else ans++;
    }
    return ans;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  Trie::Node *root = Trie::reset();
  int N; cin >> N;
  vector<string> v(N);
  F0R(i, N) {
    cin >> v[i];
    Trie::insert(root, v[i]);
  }
  F0R(i, N) {
    Trie::remove(root, v[i]);
    cout << Trie::lcp(root, v[i]) << '\n';
    Trie::insert(root, v[i]);
  }
}
