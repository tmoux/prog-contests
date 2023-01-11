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

// For each value x at index i, iterate over the divisors d of x.
// We count how many subarrays have x as the leftmost maximum.
// (1) Compute L <= i <= R, the bounds of the max subarray not containing elements > x. (Binary search with sparse table.)
// (2) For each d, compute j <= i <= k, the nearest leftmost and rightmost indices with value d.
// (3) Also precompute for each index with value d, the farthest you can go to the left/right with values all >= d. Use this to update L and R.
// Total is (i - L + 1) * (R - i + 1) - (i - j) * (k - i).
//
// Precomputation for (2) and (3) can be done in O(n log n) with sweepline over events.
// Processing each index then takes O(log n + max # of divisors) = O(log n + 240). So in total is O(n (log n + 240)).

const int maxn = 1e6+6;
vector<int> divisors[maxn];

struct Sparse {
  //sparse table data structure for max
  static const int mk = 19; //change this number based on bounds
  int* tb[mk];
  static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
  Sparse(int *a, int n) {
    for (int i = 0; i < mk; i++) {
      tb[i] = new int[n];
    }
    for (int i = 0; i < n; i++) tb[0][i] = a[i];
    for (int k = 1; k <= lg(n); k++) {
      for (int i = 0; i < n; i++) {
        int nx = i + (1<<(k-1));
        if (nx < n) tb[k][i] = max(tb[k-1][i],tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  int getmax(int l, int r) {
    int g = lg(r-l+1);
    return max(tb[g][l],tb[g][r-(1<<g)+1]);
  }
};

struct Event {
  int t, e, index, x; // type 1 = add, type 0 = delete
  bool operator<(const Event& rhs) const {
    if (t != rhs.t) return t < rhs.t;
    else return e < rhs.e;
  }
  bool operator>(const Event& rhs) const {
    return rhs < *this;
  }
};

ll solve() {
  int N; cin >> N;
  int A[N];
  map<int, vector<int>> mp;
  F0R(i, N) {
    cin >> A[i];
    mp[A[i]].push_back(i);
  }
  Sparse table(A, N);

  auto get_next_left = [&](int i) {
    if (i == 0) return i;
    int lo = -1, hi = i;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (table.getmax(mid, i-1) >= A[i] ? lo : hi) = mid;
    }
    return lo + 1;
  };
  auto get_next_right = [&](int i) {
    int lo = i, hi = N;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      (table.getmax(i, mid) == A[i] ? lo : hi) = mid;
    }
    return lo;
  };

  vector<int> closest_left(maxn, -1), closest_right(maxn, -1);
  vector<int> border_left(N), border_right(N);

  vector<Event> left_events, right_events;
  { // Process indices
    set<int> s = {-1, N};
    for (auto [x, v]: mp) {
      for (int i: v) {
        auto it = s.upper_bound(i);
        border_left[i] = *prev(it);
        border_right[i] = *it;
      }
      for (int i: v) {
        s.insert(i);
      }
      for (int i: v) {
        auto it = s.lower_bound(i);
        left_events.push_back({i, 1, i, x});
        left_events.push_back({*next(it), 0, i, x});

        right_events.push_back({*prev(it) + 1, 1, i, x});
        right_events.push_back({i + 1, 0, i, x});
      }
    }
    sort(all(left_events), greater<Event>());
    sort(all(right_events), greater<Event>());
  }

  ll ans = 0;
  F0R(i, N) {
    int L = get_next_left(i);
    int R = get_next_right(i);
    vector<pair<vector<Event>&, vector<int>&>> eventsVec = {
      {left_events, closest_left},
      {right_events, closest_right},
    };
    for (auto& [events, vec]: eventsVec) {
      while (!events.empty() && events.back().t <= i) {
        auto [_, e, idx, x] = events.back(); events.pop_back();
        vec[x] = e ? idx : -1;
      }
    }
    for (int d: divisors[A[i]]) {
      int j = closest_left[d]; // leftmost index
      int k = closest_right[d]; // rightmost index
      int LL = L, RR = R;
      if (j == -1 && k == -1) continue;
      else if (j != -1 && k == -1) {
        k = border_right[j];
        ckmax(LL, border_left[j] + 1);
        ckmin(RR, k - 1);
      }
      else if (j == -1 && k != -1) {
        j = border_left[k];
        ckmax(LL, j + 1);
        ckmin(RR, border_right[k] - 1);
      }
      else {
        ckmax(LL, border_left[j] + 1);
        ckmin(RR, border_right[k] - 1);
      }
      ckmax(j, LL - 1);
      ckmin(k, RR + 1);
      ans += 1LL * (RR - i + 1) * (i - LL + 1) - 1LL * (k - i) * (i - j);
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int i = 1; i < maxn; i++) {
    for (int j = i; j < maxn; j += i) {
      divisors[j].push_back(i);
    }
  }
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
