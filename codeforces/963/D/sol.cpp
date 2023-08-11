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

const int ALPHA = 26;
struct AhoCorasick {
  struct Node {
    int next[ALPHA], trans[ALPHA];
    int link;
    int term;
    int next_term;

    Node() : link(-1), term(-1), next_term(-1) {
      F0R(i, ALPHA) next[i] = trans[i] = -1;
    }
  };

  vector<Node> nodes;

  int newNode() {
    nodes.push_back(Node());
    return sz(nodes) - 1;
  }

  void insert(int i, const string& s, int idx) {
    for (char ch: s) {
      int c = ch - 'a';
      if (nodes[i].next[c] == -1) nodes[i].next[c] = newNode();
      i = nodes[i].next[c];
    }
    nodes[i].term = idx;
  }

  AhoCorasick(const vector<string>& vs) {
    int root = newNode();
    F0R(i, sz(vs)) {
      insert(root, vs[i], i);
    }

    queue<int> q;
    q.push(root);
    nodes[root].link = root;
    F0R(c, ALPHA) {
      nodes[root].trans[c] = nodes[root].next[c] == -1 ? root : nodes[root].next[c];
    }
    while (!q.empty()) {
      int i = q.front(); q.pop();
      F0R(ch, ALPHA) {
        if (nodes[i].next[ch] != -1) {
          int j = nodes[i].next[ch];
          if (i == root) {
            nodes[j].link = root;
          }
          else {
            nodes[j].link = nodes[nodes[i].link].trans[ch];
          }
          int suf = nodes[j].link;
          nodes[j].next_term = nodes[suf].term != -1 ? suf : nodes[suf].next_term;
          F0R(c, ALPHA) {
            if (nodes[j].next[c] != -1) {
              nodes[j].trans[c] = nodes[j].next[c];
            }
            else {
              nodes[j].trans[c] = nodes[suf].trans[c];
            }
          }
          q.push(j);
        }
      }
    }
  }

  int go(int i, int c) {
    return nodes[i].trans[c];
  }

  vector<int> get_matches(int i) {
    vector<int> r;
    while (i != -1) {
      if (nodes[i].term != -1) r.push_back(nodes[i].term);
      i = nodes[i].next_term;
    }
    return r;
  }
};

const int ALPHA = 26;

// to answer a query:
// Associate each index in s with a state in the AC automaton.
// Identify all matches, and find the subarray with min distance.

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  int Q; cin >> Q;

  vector<string> vs;
  vector<int> ks;
  F0R(i, Q) {
    int k; cin >> k;
    string t; cin >> t;
    ks.push_back(k);
    vs.push_back(t);
  }

  auto min_dist = [&](int i, const vector<int>& v) {
    if (ks[i] > sz(v)) return -1;
    int ans = 1e9;
    for (int j = 0; j + ks[i] - 1 < sz(v); j++) {
      ckmin(ans, v[j + ks[i] - 1] - (v[j] - sz(vs[i])));
    }
    return ans;
  };

  AhoCorasick AC(vs);
  int idx = 0;
  vector<vector<int>> V(Q);
  F0R(i, sz(s)) {
    char c = s[i];
    idx = AC.go(idx, c-'a');
    for (auto j: AC.get_matches(idx)) {
      V[j].push_back(i);
    }
  }

  F0R(i, Q) {
    cout << min_dist(i, V[i]) << '\n';
  }
}
