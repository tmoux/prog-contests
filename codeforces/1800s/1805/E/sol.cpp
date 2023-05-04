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
vector<pair<int, int>> adj[maxn];

int M;
pair<int, int> v[maxn];
int init_idx;

struct Tracker {
  map<int, int> cnt;
  int curmax;
  int idx = 0;
  int othermax;

  Tracker() {}
  Tracker(int _idx) {
    curmax = 0;
    idx = _idx;
  }

  void update_idx() {
    while (idx < M && v[idx].second - (cnt.count(v[idx].first) ? cnt[v[idx].first] : 0) < 2) {
      idx++;
    }
  }

  void insert(int x, int c) {
    cnt[x] += c;
    if (cnt[x] >= 2) {
      ckmax(curmax, x);
    }
    update_idx();
  }

  int getmax() {
    return max(curmax, v[idx].first);
  }
};

void merge(Tracker& a, Tracker& b) {
  if (sz(a.cnt) < sz(b.cnt)) swap(a, b);
  for (auto [x, c]: b.cnt) {
    a.insert(x, c);
  }
}

Tracker ts[maxn];
int ans[maxn];

void dfs(int i, int p) {
  ts[i] = Tracker(init_idx);
  ts[i].insert(A[i], 1);
  for (auto [j, id]: adj[i]) {
    if (j == p) continue;
    dfs(j, i);
    ans[id] = ts[j].getmax();
    merge(ts[i], ts[j]);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].emplace_back(b, i);
    adj[b].emplace_back(a, i);
  }
  map<int, int> mp;
  F0R(i, N) {
    cin >> A[i];
    mp[A[i]]++;
  }
  {
    int i = 0;
    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
      v[i++] = *it;
    }
    M = i;
    int idx = 0;
    while (idx < M && v[idx].second < 2) idx++;
    init_idx = idx;
  }

  dfs(0, 0);

  F0R(i, N-1) {
    cout << ans[i] << '\n';
  }
}
