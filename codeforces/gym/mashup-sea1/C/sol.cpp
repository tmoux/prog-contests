#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

/*
 * Let's split up queries into two types: big and small.
 * For big queries, we know that there can't be that many of them, so we can just brute force them using AC.
 * For small queries, we can maintain a count of all substrings under a certain length B using hashing.
 * The only concern is that using a hash table might be slow, so we should use gp_hash_table and try to make B relatively small.
 */

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<int, int, chash> MP;

const int ALPHA = 26;
struct AhoCorasick {
  struct Node {
    int next[ALPHA], trans[ALPHA];
    int link;
    int term;
    int next_term;
    int cnt;
    int matches_cnt;

    Node() : link(-1), term(-1), next_term(-1), cnt(0), matches_cnt(-1) {
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
    nodes[i].cnt++;
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

  ll count_suffixes(int i) {
    if (i == -1) return 0;
    int& res = nodes[i].matches_cnt;
    if (res != -1) return res;
    else return res = nodes[i].cnt + count_suffixes(nodes[i].next_term);
  }

  ll count_matches(const string& s) {
    int idx = 0;
    ll ans = 0;
    F0R(i, sz(s)) {
      char c = s[i];
      idx = go(idx, c-'a');
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
};      ans += count_suffixes(idx);
    }
    return ans;
  }
};

const int B = 200;

const int maxn = 3e5+5;
namespace HH {
  const int base = rng() % 100 + 29;
  const int M1 = 1e9+9;
  const int M2 = 1e9+21;
  ll inverse1[maxn], inverse2[maxn];
  int ctoi(char c) {return c-'a'+1;}

  ll modexp(ll x, ll n, int M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
  }

  struct Hash
  {
    int len;
    string str;
    ll *prefix1; // , *prefix2;
    Hash(const string& s) {
      len = s.size();
      str = s;
      prefix1 = new ll[len+1];
      // prefix2 = new ll[len+1];
      prefix1[0] = 0;
      // prefix2[0] = 0;
      ll mult1 = 1;
      // ll mult2 = 1;
      for (int i = 0; i < sz(s); i++) {
        prefix1[i+1] = (prefix1[i] + (ctoi(s[i])*mult1)%M1)%M1;
        mult1 = (mult1*base)%M1;

        // prefix2[i+1] = (prefix2[i] + (ctoi(s[i])*mult2)%M2)%M2;
        // mult2 = (mult2*base)%M2;
      }
    }

    int sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
      return ((prefix1[r]-prefix1[l-1]+M1)*inverse1[l-1])%M1;
    }

    ~Hash() {
      delete[] prefix1;
      // delete[] prefix2;
    }
  };

  void init_inverse() {
    inverse1[0] = 1;
    inverse1[1] = modexp(base,M1-2,M1);
    for (int i = 2; i < maxn; i++) {
      inverse1[i] = (inverse1[i-1] * inverse1[1]) % M1;
    }
    // inverse2[0] = 1;
    // inverse2[1] = modexp(base,M2-2,M2);
    // for (int i = 2; i < maxn; i++) {
    //   inverse2[i] = (inverse2[i-1] * inverse2[1]) % M2;
    // }
  }
};
using HH::Hash;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  HH::init_inverse();
  int Q; cin >> Q;
  vector<string> S;
  map<string, int> compress;
  int c = 0;

  vector<int> on;
  F0R(i, Q) {
    int t; cin >> t;
    string s; cin >> s;
    if (!compress.count(s)) {
      S.push_back(s);
      on.push_back(0);
      compress[s] = c++;
    }
    if (t == 1) {
      int idx = compress[s];
      assert(!on[idx]); on[idx] = 1;
      Hash h(s);
      MP[h.sub(1, sz(s))]++;
    }
    else if (t == 2) {
      int idx = compress[s];
      assert(on[idx]); on[idx] = 0;
      Hash h(s);
      MP[h.sub(1, sz(s))]--;
    }
    else {
      ll ans = 0;
      if (sz(s) >= B) {
        vector<string> vs;
        F0R(i, c) {
          if (on[i]) {
            vs.push_back(S[i]);
          }
        }
        AhoCorasick AC(vs);
        ans = AC.count_matches(s);
      }
      else {
        Hash h(s);
        for (int i = 1; i <= sz(s); i++) {
          for (int j = i; j <= sz(s); j++) {
            auto hsh = h.sub(i, j);
            ans += MP.find(hsh) == MP.end() ? 0 : MP[hsh];
          }
        }
      }
      cout << ans << endl;
    }
  }
}
