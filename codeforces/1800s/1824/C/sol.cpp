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

const int maxn = 1e5+5;
int N, A[maxn];
vector<int> adj[maxn];

struct Bag {
  map<int, int> freq;
  set<pair<int, int>> s;
  int aux = 0;

  void fix() {
    if (!s.empty() && s.rbegin()->first > 1) {
      auto [_, v] = mostFrequent();
      freq.clear();
      s.clear();
      for (auto x: v) {
        freq[x^aux] = 1;
        s.insert({1, x^aux});
      }
    }
  }

  bool contains(int x) {
    x ^= aux;
    return freq.count(x) && freq[x] == s.rbegin()->first;
  }

  void update(int x) {
    aux ^= x;
  }

  void insert(int x, int d) {
    x ^= aux;
    if (freq.count(x)) {
      s.erase({freq[x], x});
    }
    freq[x] += d;
    s.insert({freq[x], x});
  }

  pair<int, vector<int>> mostFrequent() {
    if (s.empty()) return {0, {}};
    assert(!s.empty());
    int f = s.rbegin()->first;
    vector<int> v;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      auto [c, x] = *it;
      if (c < f) break;
      v.push_back(x ^ aux);
    }
    return {f, v};
  }

  set<pair<int, int>> getS() {
    set<pair<int, int>> ret;
    for (auto [a, b]: s) {
      ret.insert({a, b^aux});
    }
    return ret;
  }
};

void merge(Bag& a, Bag& b) {
  if (sz(a.freq) < sz(b.freq)) swap(a, b);
  for (auto [x, c]: b.freq) {
    a.insert(x ^ b.aux, c);
  }
};

int dp[maxn];

Bag* dfs(int i, int p) {
  Bag* bi = new Bag();
  bool isLeaf = true;
  for (int j: adj[i]) {
    if (j == p) continue;
    Bag* bj = dfs(j, i);
    isLeaf = false;
    merge(*bi, *bj);
  }

  if (isLeaf) {
    bi->insert(0, 1);
    dp[i] = 0;
  }
  else {
    for (int j: adj[i]) {
      if (j == p) continue;
      dp[i] += dp[j] + 1;
    }
    dp[i] -= bi->s.rbegin()->first;
  }

  bi->update(A[i]);
  bi->fix();

  return bi;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) cin >> A[i];
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto b0 = dfs(0, 0);
  int cost = dp[0];
  cout << (b0->contains(0) ? cost : cost+1) << '\n';
}
