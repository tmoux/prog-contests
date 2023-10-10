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

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
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
    return true;
  }
};

namespace Trie {
  const int ALPHA = 26;
  struct Node {
    Node *ch[ALPHA];
    int idx;
    Node() {}
    Node(int _idx) : idx(_idx) {
      F0R(i, ALPHA) ch[i] = nullptr;
    }
  };

  const int MX = 3e6+6;
  Node nodes[MX];
  int cur = 0;
  Node* reset() {
    cur = 0;
    nodes[cur] = Node(cur);
    return &nodes[cur];
  }

  Node* newNode() {
    ++cur;
    nodes[cur] = Node(cur);
    return &nodes[cur];
  }

  int insert(Node *root, const string& s) {
    for (char c: s) {
      int i = c - 'a';
      if (!root->ch[i]) root->ch[i] = newNode();
      root = root->ch[i];
    }
    return root->idx;
  }

  void dfs(Node *root, int d, vector<vector<int>>& depth) {
    depth[d].push_back(root->idx);
    F0R(i, ALPHA) {
      if (root->ch[i]) {
        dfs(root->ch[i], d+1, depth);
      }
    }
  }
};

const int block_size = 750;
struct Query {
  int l, r, idx;
  bool operator<(Query other) const
  {
    return make_pair(l / block_size, r) <
      make_pair(other.l / block_size, other.r);
  }
};

ll solve() {
  int N; cin >> N;
  vector<string> S(N);
  Trie::Node* root = Trie::reset();
  vector<int> node(N);
  int maxdepth = 0;
  F0R(i, N) {
    cin >> S[i];
    reverse(all(S[i]));
    ckmax(maxdepth, sz(S[i]));
    node[i] = Trie::insert(root, S[i]);
  }
  vector<vector<int>> depth(maxdepth+1);
  Trie::dfs(root, 0, depth);

  int Q; cin >> Q;
  vector<vector<Query>> Qs(maxdepth+1);
  F0R(i, Q) {
    int a, b, k; cin >> a >> b >> k;
    a--, b--;

    if (k <= maxdepth) Qs[k].push_back({a, b, i});
  }

  DSU dsu(Trie::cur+1);

  const int MX = 1100;
  vector<int> cnt(Trie::cur+1), freq(MX+1);

  ll C = 0;

  vector<int> answers(Q);
  auto MO = [&](vector<Query> queries, int k) -> void {
    sort(queries.begin(), queries.end());

    // INIT
    auto add = [&](int idx) -> void {
      C++;
      if (sz(S[idx]) < k) return;
      int i = dsu.Find(node[idx]);
      freq[min(cnt[i], MX)]--;
      cnt[i]++;
      freq[min(cnt[i], MX)]++;
    };

    auto remove = [&](int idx) -> void {
      C++;
      if (sz(S[idx]) < k) return;
      int i = dsu.Find(node[idx]);
      freq[min(cnt[i], MX)]--;
      cnt[i]--;
      freq[min(cnt[i], MX)]++;
    };

    auto get_answer = [&]() -> int {
      int ans = 0;
      for (int i = 1; i <= MX; i++) {
        ans += min(freq[i], i - ans);
      }
      return ans;
    };

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
      while (cur_l > q.l) {
        cur_l--;
        add(cur_l);
      }
      while (cur_r < q.r) {
        cur_r++;
        add(cur_r);
      }
      while (cur_l < q.l) {
        remove(cur_l);
        cur_l++;
      }
      while (cur_r > q.r) {
        remove(cur_r);
        cur_r--;
      }
      answers[q.idx] = get_answer();
    }

    // reset
    for (int i = cur_l; i <= cur_r; i++) remove(i);
  };

  for (int i = maxdepth; i >= 1; i--) {
    for (auto node: depth[i]) {
      F0R(j, Trie::ALPHA) {
        Trie::Node* n = &Trie::nodes[node];
        if (n->ch[j]) dsu.Union(node, n->ch[j]->idx);
      }
    }
    MO(Qs[i], i);
  }
  DEBUG(C);
  return std::accumulate(all(answers), 0LL);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cerr << "On case " << tc << endl;
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
