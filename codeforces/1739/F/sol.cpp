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

const int ALPHA = 12;
struct AhoCorasick {
  struct Node {
    int next[ALPHA], trans[ALPHA];
    int cost = 0;
    int link;

    Node() : cost(0), link(-1) {
      F0R(i, ALPHA) next[i] = trans[i] = -1;
    }
  };

  vector<Node> nodes;

  int newNode() {
    nodes.push_back(Node());
    return sz(nodes) - 1;
  }

  void insert(int i, const string& s, int co) {
    for (char ch: s) {
      int c = ch - 'a';
      if (nodes[i].next[c] == -1) nodes[i].next[c] = newNode();
      i = nodes[i].next[c];
    }
    nodes[i].cost += co;
  }

  AhoCorasick(const vector<string>& vs, const vector<int>& cs) {
    int root = newNode();
    F0R(i, sz(vs)) {
      insert(root, vs[i], cs[i]);
    }

    queue<int> q;
    q.push(root);
    nodes[root].link = root;
    F0R(c, ALPHA) {
      nodes[root].trans[c] = nodes[root].next[c] == -1 ? root : nodes[root].next[c];
    }
    while (!q.empty()) {
      int i = q.front(); q.pop();
      nodes[i].cost += nodes[nodes[i].link].cost;
      F0R(ch, ALPHA) {
        if (nodes[i].next[ch] != -1) {
          int j = nodes[i].next[ch];
          if (i == root) {
            nodes[j].link = root;
          }
          else {
            nodes[j].link = nodes[nodes[i].link].trans[ch];
          }
          F0R(c, ALPHA) {
            if (nodes[j].next[c] != -1) {
              nodes[j].trans[c] = nodes[j].next[c];
            }
            else {
              nodes[j].trans[c] = nodes[nodes[j].link].trans[c];
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
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<string> vs;
  vector<int> cs;

  auto get_string = [&](string s) -> std::optional<string> {
    deque<char> deq = {s[0]};
    int idx = 0;
    set<char> S = {s[0]};
    FOR(i, 1, sz(s)) {
      if (idx + 1 < sz(deq) && deq[idx+1] == s[i]) idx++;
      else if (idx - 1 >= 0 && deq[idx-1] == s[i]) idx--;
      else if (idx + 1 == sz(deq) && !S.count(s[i])) {
        S.insert(s[i]);
        deq.push_back(s[i]), idx++;
      }
      else if (idx == 0 && !S.count(s[i])) {
        S.insert(s[i]);
        deq.push_front(s[i]);
      }
      else return std::nullopt;
    }
    string t;
    for (char c: deq) t += c;
    return t;
  };
  F0R(i, N) {
    int c; cin >> c;
    string s; cin >> s;

    auto mt = get_string(s);
    if (mt) {
      string t = *mt;
      vs.push_back(t);
      cs.push_back(c);
      reverse(all(t));
      vs.push_back(t);
      cs.push_back(c);
    }
  }

  AhoCorasick AC(vs, cs);
  vector<vector<int>> dp(1 << ALPHA, vector<int>(4005, -1));
  vector<vector<pair<int, int>>> recon(1 << ALPHA, vector<pair<int, int>>(4005));
  auto f = y_combinator([&](auto f, int mask, int s) -> int {
    int& res = dp[mask][s];
    if (res != -1) return res;
    if (mask == (1 << ALPHA) - 1) return res = 0;
    F0R(i, ALPHA) {
      if (!(mask & (1 << i))) {
        int nmask = mask | (1 << i);
        int ns = AC.go(s, i);
        if (ckmax(res, f(nmask, ns) + AC.nodes[ns].cost)) {
          recon[mask][s] = {nmask, ns};
        }
      }
    }
    return res;
  });

  f(0, 0);
  int mask = 0, s = 0;
  string ans;
  while (__builtin_popcount(mask) < ALPHA) {
    auto [nmask, ns] = recon[mask][s];
    int c = 31 - __builtin_clz(mask ^ nmask);
    ans += 'a' + c;
    std::tie(mask, s) = {nmask, ns};
  }
  cout << ans << '\n';
}
