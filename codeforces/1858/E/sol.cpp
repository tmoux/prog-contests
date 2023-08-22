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

// https://usaco.guide/adv/persistent?lang=cpp
struct Node {
  Node *l, *r;

  Node(ll x) : l(nullptr), r(nullptr) {}
  Node(Node *ll, Node *rr) : l(ll), r(rr) {}
};

const int MX = 1e6+6;
int n = MX, a[MX];     // The initial array and its size
Node *roots[MX];  // The persistent array's roots

Node *build(int l = 0, int r = n - 1) {
  if (l == r) return new Node(a[l]);
  int mid = (l + r) / 2;
  return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *node, int val, int pos, int l = 0, int r = n - 1) {
  if (l == r) return new Node(val);
  int mid = (l + r) / 2;
  if (pos > mid)
    return new Node(node->l, update(node->r, val, pos, mid + 1, r));
  else return new Node(update(node->l, val, pos, l, mid), node->r);
}

int query(Node *node, int pos, int l = 0, int r = n - 1) {
  if (l == r) return (node != nullptr);
  if (!node) return 0;
  int mid = (l + r) / 2;
  if (pos > mid) return query(node->r, pos, mid + 1, r);
  return query(node->l, pos, l, mid);
}

int get_item(int index, int time) {
  // Gets the array item at a given index and time
  return query(roots[time], index);
}

void update_item(int index, int value, int prev_time, int curr_time) {
  // Updates the array item at a given index and time
  roots[curr_time] = update(roots[prev_time], index, value);
}

void init_arr(int nn, int *init) {
  // Initializes the persistent array, given an input array
  n = nn;
  for (int i = 0; i < n; i++) a[i] = init[i];
  roots[0] = build();
}

int num_distinct[MX];
const int MK = 20;
int par[MK][MX];

int jump(int i, int k) {
  F0Rd(j, MK) {
    if (k & (1 << j)) {
      i = par[j][i];
    }
  }
  return i;
}

// DS: use persistent array
// + add new node, increment num distinct if needed
// - jump up k ancestors
// ! Go to previous node (maintain stack, to previous position)
// ? just query num distinct

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  roots[0] = new Node(nullptr, nullptr);
  int cur_idx = 0, nxt = 1;

  int Q; cin >> Q;
  stack<int> st; // points to previous node
  while (Q--) {
    char c; cin >> c;
    if (c == '+') {
      int x; cin >> x;
      int cnt = query(roots[cur_idx], x);
      num_distinct[nxt] = num_distinct[cur_idx] + (cnt == 0 ? 1 : 0);
      roots[nxt] = update(roots[cur_idx], cnt+1, x);
      par[0][nxt] = cur_idx;
      for (int i = 1; i < MK; i++) {
        par[i][nxt] = par[i-1][par[i-1][nxt]];
      }
      st.push(cur_idx);
      cur_idx = nxt;
      nxt++;
    }
    else if (c == '-') {
      int k; cin >> k;
      st.push(cur_idx);
      cur_idx = jump(cur_idx, k);
    }
    else if (c == '!') {
      assert(!st.empty());
      cur_idx = st.top(); st.pop();
    }
    else if (c == '?') {
      cout << num_distinct[cur_idx] << endl;
    }
    else assert(false);
  }
}
