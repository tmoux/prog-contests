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
    vector<pair<int, Node*>> ch;
    int sum;
    int cnt;
    Node() : sum(0), cnt(0) {
    }

    bool count(int c) {
      for (auto& [x, _]: ch) {
        if (x == c) return true;
      }
      return false;
    }

    Node* get(int c) {
      for (auto& [x, n]: ch) {
        if (x == c) return n;
      }
      return nullptr;
    }

    void add(int c, Node* n) {
      ch.push_back({c, n});
    }
  };

  const int MX = 1e6+6;
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

  void insert(Node *root, const string& s) {
    root->sum += sz(s);
    root->cnt++;

    F0R(i, sz(s)) {
      int c = s[i] - 'a';
      if (!root->count(c)) root->add(c, newNode());
      root = root->get(c);
      root->sum += sz(s);
      root->cnt++;
    }
  }

  void count(Node *root, const string& t, ll& ans) {
    for (int i = 0; i <= sz(t); i++) {
      if (!root) break;
      int sumMatch = root->sum;
      int numMatch = root->cnt;
      if (i < sz(t)) {
        int c = t[i] - 'a';
        for (auto& [x, n]: root->ch) {
          if (x == c) {
            sumMatch -= n->sum;
            numMatch -= n->cnt;
          }
        }
      }

      ans += 1LL * numMatch * sz(t);
      ans += sumMatch;
      ans -= 2LL * i * numMatch;

      if (i < sz(t)) root = root->get(t[i] - 'a');
    }
  }
};
using namespace Trie;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<string> S(N);
  Node *root = reset();
  F0R(i, N) {
    cin >> S[i];
    insert(root, S[i]);
  }

  ll ans = 0;
  F0R(i, N) {
    string t = S[i];
    reverse(all(t));
    count(root, t, ans);
  }
  cout << ans << '\n';
}
