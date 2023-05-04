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
    Node *ch[2];
    int cnt;
    Node() : cnt(0) {
      ch[0] = ch[1] = nullptr;
    }
  };

  const int MX = 6e6+6;
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

  void remove(Node* root, int x) {
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      assert(root->ch[c]);
      root = root->ch[c];
      root->cnt--;
    }
  }

  int get_min_xor(Node* root, int x) {
    int res = 0;
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      if (root->ch[c] && root->ch[c]->cnt > 0) {
        root = root->ch[c];
      }
      else {
        res |= 1 << i;
        root = root->ch[c^1];
      }
    }
    return res;
  }
};

struct DSU {
  int n;
  vector<int> par;
  vector<vector<int>> comp;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
    comp.resize(n+1);
    F0R(i, n) comp[i].push_back(i);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    for (auto i: comp[y]) comp[x].push_back(i);
    comp[y].clear();
    return true;
  }

  int size(int i) {
    return -par[Find(i)];
  }
};

const int maxn = 2e5+5, maxk = 30;
int N, A[maxn];

map<int, vector<int>> S;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  Trie::Node *root = Trie::reset();
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
    S[A[i]].push_back(i);
    Trie::insert(root, A[i]);
  }

  DSU dsu(N);
  for (auto [x, v]: S) {
    F0R(i, sz(v)-1) {
      dsu.Union(v[i], v[i+1]);
    }
  }
  using P = pair<int, int>;
  using PQ = priority_queue<P, vector<P>, greater<P>>;
  PQ pq;

  F0R(i, N) {
    if (dsu.Find(i) == i) {
      pq.push({dsu.size(i), i});
    }
  }

  ll ans = 0;
  while (sz(pq) > 1) {
    auto [sz, i] = pq.top(); pq.pop();
    if (sz != dsu.size(i)) continue;
    // cout << i << ' ' << sz << endl;
    vector<int> v = dsu.comp[dsu.Find(i)];
    for (auto j: v) {
      Trie::remove(root, A[j]);
    }

    pair<int, int> mn = {1e9, 1e9};
    for (auto j: v) {
      int x = Trie::get_min_xor(root, A[j]);
      ckmin(mn, {x, x^A[j]});
    }

    ans += mn.first;
    assert(!S[mn.second].empty());
    int k = *S[mn.second].begin();
    k = dsu.Find(k);
    dsu.Union(i, k);
    k = dsu.Find(k);
    pq.push({dsu.size(k), k});

    for (auto j: v) {
      Trie::insert(root, A[j]);
    }
    // cout << pq << endl;
  }

  cout << ans << '\n';
}
