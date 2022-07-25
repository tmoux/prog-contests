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

const int maxn = 10;
int N, K, M;

int target[maxn];
int color_mask[maxn];

int equip_mask[maxn];

int dist[1<<maxn][1<<maxn]; // correct state, covered state

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K >> M;
  int ALL = (1<<N) - 1;
  F0R(i, N) {
    cin >> target[i]; // color between 1 .. K
    target[i]--; // make 0-indexed 0 .. K-1

    color_mask[target[i]] |= 1<<i; // add to mask
  }
  F0R(i, M) {
    int r; cin >> r;
    F0R(j, r) {
      int x; cin >> x; x--;
      equip_mask[i] |= 1<<x;
    }
  }

  memset(dist, -1, sizeof dist);
  queue<pair<int, int>> q;
  // 0 = uncovered, 1 = covered
  pair<int, int> init = {color_mask[0], 0};
  q.push(init);
  dist[init.first][init.second] = 0;

  while (!q.empty()) {
    auto [a, b] = q.front(); q.pop();
    if (a == ALL && b == 0) {
      cout << dist[a][b] << '\n';
      return 0;
    }
    auto go_state = [&](int na, int nb) {
      if (dist[na][nb] == -1) {
        dist[na][nb] = dist[a][b] + 1;
        q.push({na, nb});
      }
    };
    // try add/remove equipment
    F0R(i, M) {
      go_state(a, b ^ (1<<i));
    }
    // try immerse
    int covered = 0;
    F0R(i, M) {
      if (b & (1<<i)) {
        covered |= equip_mask[i];
      }
    }
    int uncovered = ALL ^ covered;

    F0R(i, K) {
      int na = (a & covered) | (color_mask[i] & uncovered);

      go_state(na, b);
    }
  }
  cout << -1 << '\n';
}
