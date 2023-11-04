#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

namespace Trie {
  struct Node {
    Node *ch[2];
    Node() {
      ch[0] = ch[1] = nullptr;
    }
  };

  const int MX = 8e6+6;
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
    }
  }

  int get_max_xor(Node* root, int x) {
    int res = 0;
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      if (root->ch[c^1]) {
        res |= 1 << i;
        root = root->ch[c^1];
      }
      else root = root->ch[c];
    }
    return res;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> A(N-1);
  for (auto& x: A) cin >> x;

  vector<int> P(N-1);
  vector<int> used(2*N);
  Trie::Node* root = Trie::reset();
  F0R(i, N-1) {
    P[i] = A[i];
    if (i > 0) P[i] ^= P[i-1];
    Trie::insert(root, P[i]);
    used[P[i]] = 1;
  }

  F0R(i, N) {
    if (Trie::get_max_xor(root, i) < N) {
      cout << i << ' ';
      for (int x: P) cout << (i ^ x) << ' ';
      cout << '\n';
      return 0;
    }
  }
  assert(false);
}