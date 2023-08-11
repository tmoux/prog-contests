#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
  Node* child[2];
  Node() {
    child[0] = child[1] = nullptr;
  }
};

void insert(Node *node, int ai, int d) {
  if (d == -1) return;
  int nxt = (ai>>d) & 1;
  if (!node->child[nxt]) node->child[nxt] = new Node();
  insert(node->child[nxt], ai, d-1);
}

int min_xor(Node *node, int x, int d) {
  if (d == -1) return 0;
  int nxt = (x>>d) & 1;
  if (node->child[nxt]) return min_xor(node->child[nxt], x, d-1);
  else return min_xor(node->child[nxt^1], x, d-1) + (1<<d);
}

int max_xor(Node *node, int x, int d) {
  if (d == -1) return 0;
  int nxt = (x>>d) & 1;
  if (node->child[nxt^1]) return max_xor(node->child[nxt^1], x, d-1) + (1<<d);
  else return max_xor(node->child[nxt], x, d-1);
}

int solve() {
  int L, R; cin >> L >> R;
  int n = R-L+1;
  vector<int> a(n);

  Node *root = new Node();
  const int maxd = 17;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    insert(root, a[i], maxd);
  }
  for (auto ai: a) {
    int x = L ^ ai;
    if (min_xor(root, x, maxd) == L &&
        max_xor(root, x, maxd) == R) {
      return x;
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
