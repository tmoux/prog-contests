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

const int MX = 1e5+5;
vector<int> v[MX];
int A[MX];

vector<int> get_divisors(int x) {
  vector<int> d;
  for (int i = 1; i*i <= x; i++) {
    if (x % i == 0) {
      d.push_back(i);
      if (x / i > i) d.push_back(x / i);
    }
  }
  sort(all(d));
  return d;
}

int solve() {
  int N, M; cin >> N >> M;

  vector<int> V;
  F0R(i, N) {
    int ai; cin >> ai;
    A[ai] = 1;
    V.push_back(ai);
  }
  sort(all(V)); V.erase(unique(all(V)), V.end());

  vector<pair<int, int>> updates;
  multiset<int> ms;
  for (int i: V) {
    for (int d: get_divisors(i)) {
      if (d <= M) {
        v[d].push_back(i);
        updates.push_back({i, d});
      }
    }
  }
  FOR(i, 1, M+1) {
    // for (int j = i; j < MX; j += i) {
    //   if (A[j]) {
    //     v[i].push_back(j);
    //     updates.push_back({j, i});
    //   }
    // }
    v[i].push_back(1e9);
    sort(all(v[i]));
    reverse(all(v[i]));
    ms.insert(v[i].back());
    // cout << v[i] << endl;
  }
  sort(all(updates)); reverse(all(updates));

  // cout << *ms.rbegin() << endl;

  int ans = 1e9;
  for (int i: V) {
    while (!updates.empty() && updates.back().first < i) {
      auto [_, j] = updates.back(); updates.pop_back();
      int t = v[j].back(); v[j].pop_back();
      // cout << i << " updating " << j << endl;
      assert(!v[j].empty());
      auto it = ms.find(t);
      assert(it != ms.end());
      ms.erase(it);
      ms.insert(v[j].back());
    }

    int d = *ms.rbegin() - i;
    ckmin(ans, d);
  }

  FOR(i, 1, M+1) {
    v[i].clear();
  }
  for (int i: V) A[i] = 0;

  return ans < 1e8 ? ans : -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
