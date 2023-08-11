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

vector<int> z_function(string s) {
  int n = (int) s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

struct Node {
  Node* ch[26];
  vector<pair<int, int>> vs; // id, index
  Node() {
    F0R(i, 26) ch[i] = nullptr;
  }
};

void add(Node* root, int id, string t) {
  F0R(i, sz(t)) {
    int c = t[i] - 'a';
    if (!root->ch[c]) root->ch[c] = new Node();
    root = root->ch[c];
    root->vs.push_back({id, i});
  }
}


const int maxn = 1e5+5;
vector<int> ans[maxn];


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  int N = sz(s);
  string t = s + "#" + s;
  auto z = z_function(t);

  Node* root = new Node();
  int Q; cin >> Q;
  vector<string> strings(Q);
  F0R(i, Q) {
    string t; cin >> t;
    strings[i] = t;
    ans[i].resize(sz(t));
    add(root, i, t);
    F0R(j, sz(t)) {
      for (int k = 0; j+k < sz(t) && k < N; k++) {
        if (s[k] != t[j+k]) break;
        ckmax(ans[i][j+k], k+1);
      }
    }
    if (sz(s) == 1) {
      string S = s + t;
      F0R(j, sz(t)) {
        for (int k = 0; j+k < sz(t); k++) {
          if (S[k] != S[1+j+k]) break;
          ckmax(ans[i][j+k], k+1);
        }
      }
    }
  }

  for (int i = N+2; i < sz(z); i++) {
    if (z[i] == 2*N+1 - i) {
      // go down at most 10, updating as we go
      // clear prefixes as we go (don't need to update them again)
      Node* cur = root;
      bool broke = false;
      int idx = z[i];
      for (; idx < min(N, z[i] + 10); idx++) {
        cur->vs.clear();
        int c = s[idx] - 'a';
        if (!cur->ch[c]) {
          broke = true;
          break;
        }
        cur = cur->ch[c];
        for (auto [id, j]: cur->vs) {
          ckmax(ans[id][j], z[i] + j + 1);
        }
      }
      if (!broke) {
        if (idx == N) {
          for (auto [id, j]: cur->vs) {
            const string& t = strings[id];
            for (int k = 0; j+k+1 < sz(t); k++) {
              if (t[k] != t[j+k+1]) break;
              ckmax(ans[id][j+k+1], z[i] + j+k+2);
            }
          }
        }
        cur->vs.clear();
      }
    }
  }

  // output answer
  F0R(i, Q) {
    for (auto x: ans[i]) {
      cout << x << ' ';
    }
    cout << '\n';
  }
}
