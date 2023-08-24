#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

namespace Trie {
  struct Node {
    int cnt;
    Node *ch[2];
    Node() : cnt(0) {
      ch[0] = ch[1] = nullptr;
    }
  };

  const int MX = 1e7+6;
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

  void insert(Node *root, int x) {
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      if (!root->ch[c]) root->ch[c] = newNode();
      root = root->ch[c];
      root->cnt++;
    }
  }

  int get_min_xor(Node* root, int x) {
    int res = 0;
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      if (root->ch[c] && root->ch[c]->cnt > 0) {
        root = root->ch[c];
        root->cnt--;
      }
      else {
        res |= 1 << i;
        root = root->ch[c^1];
        assert(root->cnt > 0);
        root->cnt--;
      }
    }
    return res;
  }
};
using namespace Trie;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];

  Node* root = reset();
  F0R(i, N) {
    int x; cin >> x;
    insert(root, x);
  }

  F0R(i, N) {
    int min_xor = get_min_xor(root, A[i]);
    cout << min_xor << ' ';
  }
  cout << '\n';
}
