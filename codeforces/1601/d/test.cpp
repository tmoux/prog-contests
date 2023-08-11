#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
    class y_combinator_result {
      Fun fun_;
      public:
      template<class T>
        explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

      template<class ...Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template<class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

  template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

struct Fenwick/*{{{*/
{
  int n;
  vector<int> bit;
  Fenwick(int n_) {
    n = n_+1;
    bit.resize(n+1,0);
  }
  void add(int i, int x) {
    i++;
    for (; i <= n; i += i & (-i))
      bit[i] += x;
  }

  int sum(int i) {
    i++;
    int r = 0;
    for (; i; i -= i & (-i)) {
      r += bit[i];
    }
    return r;
  }
};/*}}}*/

// coordinates are in range [0, n)
// starting difficulty is d
int solve(vector<pair<int,int>> ps, int n, int d) {
  sort(all(ps));

  vector<bool> hasy(n+1, false);
  for (auto [_, y]: ps) hasy[y] = true;

  map<int, vector<int>> vert;
  for (auto [x, y]: ps) vert[x].push_back(y);

  vector<pair<int,int>> next_point(n);
  {
    vector<int> horiz(n+1, -1);
    horiz[n] = n;
    int min_y = n;
    for (int i = n-1; i >= d; i--) {
      if (vert.count(i)) {
        for (auto y: vert[i]) {
          horiz[y] = i;
          if (i < y) ckmin(min_y, y);
        }
      }
      next_point[i] = {horiz[min_y], min_y};
      if (horiz[i] != -1) min_y = i;
    }
  }

  vector<int> dp(n+1, 0);

  vector<map<int, int>> queryMap(n);

  auto calc_trans = [&](int i, int x, int y) -> int {
    return dp[y] + queryMap[i][y-1] - queryMap[i][i-1] + (x < y ? 1 : 0);
  };

  vector<pair<int,int>> queries;
  queries.reserve(3*n);

  vector<vector<pair<int,int>>> checks(n);
  for (int i = n-1; i >= d; i--) {
    if (i != d && !hasy[i]) continue;
    auto [x, y] = next_point[i];
    queries.push_back({i-1, i});
    queries.push_back({y-1, i});

    auto start = vert.lower_bound(i);
    auto end = vert.upper_bound(y);
    for (auto itx = start; itx != end; ++itx) {
      for (auto it = upper_bound(all(itx->second), y); it != itx->second.end(); ++it) {
        int yy = *it;
        queries.push_back({yy-1, i});

        checks[i].push_back({itx->first, yy});
      }
    }
  }

  // process queries
  sort(all(queries));
  Fenwick fen(n);
  {
    int curx = 0;
    for (auto [x, y]: queries) {
      while (curx <= x) {
        if (vert.count(curx)) {
          for (auto yy: vert[curx]) {
            fen.add(yy, 1);
          }
        }
        curx++;
      }
      if (!queryMap[y].count(x)) {
        queryMap[y][x] = fen.sum(y);
      }
    }
  }

  for (int i = n-1; i >= d; i--) {
    if (i != d && !hasy[i]) continue;
    auto [x, y] = next_point[i];
    ckmax(dp[i], calc_trans(i, x, y));

    for (auto [xx, yy]: checks[i]) {
      ckmax(dp[i], calc_trans(i, xx, yy));
    }
  }

  return dp[d];
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


// For each point (x, x) on the line y = x, find the "next" point with strictly higher y-coordinate, and least possible x-coordinate, call this (x', y')
// Check transitioning to this point, and all points "in between" (with x-coordinate in the range [x, y'), and y-coordinate > y')

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n = 500000;
  int d = 0;
  vector<int> a(2*n+1);
  vector<pair<int,int>> pairs(2*n+1);
  for (int i = 0; i < n; i++) {
    int x = rng() % 100000000;
    int y = rng() % 100000000;

    a[2*i] = x;
    a[2*i+1] = y;
    pairs[2*i] = {x, 2*i};
    pairs[2*i+1] = {y, 2*i+1};
  }
  a[2*n] = d;
  pairs[2*n] = {d, 2*n};
  sort(all(pairs));
  int nxt = 0;
  for (int i = 0; i < sz(pairs); i++) {
    if (i > 0 && pairs[i-1].first != pairs[i].first) nxt++;
    a[pairs[i].second] = nxt;
  }

  d = a[2*n];
  vector<pair<int,int>> points(n);
  F0R(i, n) {
    points[i].first = a[2*i];
    points[i].second = a[2*i+1];
  }

  int ans = solve(points, nxt+1, d);
  cout << ans << '\n';
}


