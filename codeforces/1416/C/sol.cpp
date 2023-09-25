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
    Node *ch[2];
    vector<int> indices;
    ll T = 0, x = 0;
    Node() {
      ch[0] = ch[1] = nullptr;
    }
  };

  const int MX = 4e6+7;
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

  void insert(Node *root, int x, int idx) {
    F0Rd(i, 30) {
      int c = (x >> i) & 1;
      if (!root->ch[c]) root->ch[c] = newNode();
      root = root->ch[c];
    }
    root->indices.push_back(idx);
  }

  void dfs_prep(Node* cur, int d, vector<array<ll, 2>>& res) {
    F0R(i, 2) if (cur->ch[i]) dfs_prep(cur->ch[i], d+1, res);
    auto vl = cur->ch[0] ? cur->ch[0]->indices : vector<int>();
    auto vr = cur->ch[1] ? cur->ch[1]->indices : vector<int>();
    int cl = sz(vl);
    int cr = sz(vr);
    cur->T = 1LL * cl * cr;

    for (int i = 0, j = 0; i < cl || j < cr;) {
      if (i < cl && (j == cr || vl[i] < vr[j])) {
        cur->indices.push_back(vl[i++]);
        cur->x += j;
      }
      else cur->indices.push_back(vr[j++]);
    }
    res[d][0] += cur->x;
    res[d][1] += cur->T - cur->x;
    // cout << "node " << cur->indices << ' ' << cur->T << ' ' << cur->x << endl;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  Trie::Node* root = Trie::reset();
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
    Trie::insert(root, A[i], i);
  }

  vector<array<ll, 2>> ans(30);
  Trie::dfs_prep(root, 0, ans);

  ll total = 0;
  ll x = 0;
  // cout << ans << endl;
  F0R(i, 30) {
    if (ans[i][0] <= ans[i][1]) {
      total += ans[i][0];
    }
    else {
      x |= 1 << (29 - i);
      total += ans[i][1];
    }
  }

  cout << total << ' ' << x << '\n';
}
