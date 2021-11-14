#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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

// }}}

struct Node {
  int min_val, max_val;

};

struct SingNode : Node {
  SingNode() {
    min_val = 0;
    max_val = 1;
  };
};

struct PlusNode : Node {
  Node *left, *right;
  PlusNode(Node* _left, Node* _right) : left(_left), right(_right) {
    min_val = left->min_val + right->min_val;
    max_val = left->max_val + right->max_val;
  }

  ~PlusNode() {
    delete left;
    delete right;
  }
};

struct MinusNode : Node {
  Node *left, *right;
  MinusNode(Node* _left, Node* _right) : left(_left), right(_right) {
    min_val = left->min_val - right->max_val;
    max_val = left->max_val - right->min_val;
  }

  ~MinusNode() {
    delete left;
    delete right;
  }
};

void solve() {
  string S; cin >> S;
  int n = sz(S);

  vector<Node*> nodes(n, nullptr);
  auto parse_node = y_combinator([&nodes, &S](auto parse_node, int idx) -> pair<Node*, int> {
      //returns length 
      if (S[idx] == '?') {
        nodes[idx] = new SingNode();
        return {nodes[idx], 1};
      }
      else {
        assert(S[idx] == '(');
        auto [node_left, len_left] = parse_node(idx+1);
        char op = S[idx+len_left+1];
        auto [node_right, len_right] = parse_node(idx+len_left+2);

        int len = len_left + len_right + 3;
        if (op == '+') {
          nodes[idx] = new PlusNode(node_left, node_right);
        }
        else if (op == '-') {
          nodes[idx] = new MinusNode(node_left, node_right);
        }
        else assert(false);
        return {nodes[idx], len};

      }
  });

  auto [root, len] = parse_node(0);
  assert(len == n);

  int Q; cin >> Q;
  F0R(_, Q) {
    int l, r; cin >> l >> r;
    l--; r--;
    assert(nodes[l] != nullptr);
    cout << nodes[l]->max_val << ' ';
  }
  cout << '\n';

  delete root;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
