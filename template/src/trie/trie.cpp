namespace Trie {
  struct Node {
    Node *ch[2];
    Node() {
      ch[0] = ch[1] = nullptr;
    }
  };

  const int MX = 3e6+6;
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
