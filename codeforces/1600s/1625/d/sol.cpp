#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

const int maxn = 3e5+5;
int N, X;

struct Node {
  Node* child[2];
  int val = -1;
  int id = -1;
  Node() {
    child[0] = child[1] = nullptr;
  }
};

void insert(Node* cur, int x, int id) {
  for (int i = 30; i >= 0; i--) {
    int c = (x>>i) & 1;
    if (!cur->child[c]) cur->child[c] = new Node();
    cur = cur->child[c];
  }
  cur->val = x;
  cur->id = id;
} 

vector<pair<int,int>> gather(Node* cur) {
  if (cur == nullptr) return {};
  if (cur->id != -1) return {{cur->val, cur->id}};
  vector<pair<int,int>> r;
  auto u = gather(cur->child[0]);
  auto v = gather(cur->child[1]);
  r.insert(r.end(), all(u));
  r.insert(r.end(), all(v));
  return r;
}

pair<int,int> max_xor(Node* cur, int x, int i, int add) {
  if (i == -1) return {add, cur->id};
  int c = (x>>i) & 1;
  if (cur->child[!c]) {
    return max_xor(cur->child[!c], x, i-1, add+(1<<i));
  }
  else {
    return max_xor(cur->child[c], x, i-1, add);
  }
}

vector<int> solve(Node* cur, int i) {
  if (cur == nullptr) return {};
  if (i == -1) return {cur->id};

  if (X & (1<<i)) {
    auto v = gather(cur->child[0]);
    if (v.empty()) return {gather(cur->child[1])[0].second};
    else {
      pair<int,pair<int,int>> mx = {-1, {-1,-1}};
      for (auto [x, id1]: v) {
        auto [xor_, id2] = max_xor(cur, x, i, 0);
        ckmax(mx, {xor_, {id1, id2}});
      }
      if (mx.first >= X) {
        return {mx.second.first, mx.second.second};
      }
      else {
        return {v[0].second};
      }
    }
  }
  else {
    auto u = solve(cur->child[0], i-1);
    auto v = solve(cur->child[1], i-1);
    vector<int> r;
    r.insert(r.end(), all(u));
    r.insert(r.end(), all(v));
    return r;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> X;
  // Special case: if X = 0, then print all
  // Otherwise, we cannot have duplicates, so might as well ignore them
  if (X == 0) {
    cout << N << '\n';
    for (int i = 1; i <= N; i++) {
      cout << i << " \n"[i == N];
    }
  }
  else {
    Node *root = new Node();
    for (int i = 1; i <= N; i++) {
      int x; cin >> x;
      insert(root, x, i);
    }

    vector<int> ans = solve(root, 30);

    if (sz(ans) >= 2) {
      cout << sz(ans) << '\n';
      for (int i: ans) {
        cout << i << ' ';
      }
      cout << '\n';
    }
    else {
      cout << -1 << '\n';
    }
  }
}
