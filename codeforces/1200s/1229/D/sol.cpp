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

const int maxn = 2e5+5;
int N, K;
vector<int> PP[maxn];
using perm = vector<int>;
using group = vector<perm>;

perm operator*(perm a, perm b) {
  perm r(K);
  F0R(i, K) {
    r[i] = b[a[i]];
  }
  return r;
}

map<perm, int> mp;
const int MX = 120;
int T[MX][MX];
int P = 0;

bitset<MX> closure(vector<int> g) {
  bitset<MX> r; r[0] = 1;
  queue<int> q; q.push(0);
  while (!q.empty()) {
    int c = q.front(); q.pop();
    for (int p: g) {
      int nc = T[p][c];
      if (!r[nc]) {
        r[nc] = 1;
        q.push(nc);
      }
    }
  }
  return r;
}

bool containedIn(vector<int> g, int i) {
  return g[i];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  F0R(i, N) {
    PP[i].resize(K);
    F0R(j, K) {
      cin >> PP[i][j];
      PP[i][j]--;
    }
  }

  vector<int> p(K); iota(all(p), 0);
  vector<vector<int>> perms;
  do {
    mp[p] = P++;
    perms.push_back(p);
  } while (next_permutation(all(p)));
  F0R(i, P) {
    F0R(j, P) {
      T[i][j] = mp[perms[i] * perms[j]];
    }
  }

  ll ans = 0;
  vector<pair<int, bitset<MX>>> groups;
  F0R(r, N) {
    vector<int> generators = {mp[PP[r]]};
    bitset<MX> curGroup = closure(generators);

    vector<pair<int, bitset<MX>>> ngroups = {{r, curGroup}};
    for (auto [i, g]: groups) {
      int idx = mp[PP[i]];
      if (!curGroup[idx]) {
        generators.push_back(idx);
        curGroup = closure(generators);
        ngroups.push_back({i, curGroup});
      }
    }
    groups = ngroups;
    F0R(i, sz(groups)) {
      int len = groups[i].first - (i + 1 < sz(groups) ? groups[i+1].first : -1);
      ans += groups[i].second.count() * len;
    }
  }
  cout << ans << '\n';
}
