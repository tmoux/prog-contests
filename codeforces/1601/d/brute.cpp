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

namespace seg2d {
  struct SegDyn
  {
    int s, e; //represents range [s,e]
    SegDyn *l, *r;
    int sum; //sum for this interval
    SegDyn(int _s, int _e) {
      s = _s;
      e = _e;
      l = NULL;
      r = NULL;
      sum = 0;
    }

    void prepareL() { if (l == NULL) l = new SegDyn(s,(s+e)/2); }
    void prepareR() { if (r == NULL) r = new SegDyn((s+e)/2+1,e); }

    void pull() {
      sum = 0;
      if (l) sum += l->sum;
      if (r) sum += r->sum;
    }

    void add(int idx, int del) { //a[idx] += del
      //cout << s << ' ' << e << '\n';
      if (s == e && s == idx) {
        //at the node, stop
        sum += del;
        return;
      }
      if (idx <= (s+e)/2) {
        prepareL();
        assert(l);
        l->add(idx,del);
      }
      else {
        prepareR();
        r->add(idx,del);
      }
      pull(); //updates current node based on the children
    }

    int getsum(int se, int en) {
      if (se > en) return 0;
      if (se <= s && e <= en) return sum;
      int res = 0;
      if (l && se <= (s+e)/2) res += l->getsum(se,en);
      if (r && en > (s+e)/2) res += r->getsum(se,en);
      return res;	
    }
  };

  const int maxn = 1e6+5;
  SegDyn* bit[maxn];
  int N;

  void add(int i, int y, int del) {
    i++;
    if (i > N) return;
    for (; i <= N; i += i & (-i))
      bit[i]->add(y,del);
  }

  int sum(int i, int y1, int y2) {
    i++;
    if (i <= 0) return 0;
    assert(1 <= i && i <= N);
    int r = 0;
    for (; i; i -= i & (-i)) {
      r += bit[i]->getsum(y1,y2);
    }
    return r;
  }

  int getRangeSum(int x1, int x2, int y1, int y2) {
    return sum(x2,y1,y2) - sum(x1-1,y1,y2); 
  }
} // namespace seg2d
using namespace seg2d;

// coordinates are in range [0, n)
// starting difficulty is d
int solve(vector<array<int,2>> ps, int n, int d) {
  ps.push_back({n, n});
  sort(all(ps));

  vector<bool> hasy(n+1, false);
  for (auto [_, y]: ps) hasy[y] = true;

  map<int, deque<int>> horiz;
  horiz[n].push_back(n);

  map<int, vector<int>> vert;
  for (auto [x, y]: ps) vert[x].push_back(y);

  vector<int> dp(n+1, 0);

  /*
     for (auto [x, y]: ps) {
     cout << x << ' ' << y << endl;
     }
     cout << "---\n";
     */

  auto next_point = [&](int i) -> array<int,2> {
    auto it = horiz.upper_bound(i);
    assert(it != horiz.end());
    assert(!it->second.empty());
    return {it->second[0], it->first};
  };

  auto get_between = [&](int i, int y) -> vector<array<int,2>> {
    vector<array<int,2>> ret;
    for (int x = i; x < y; x++) {
      for (auto it = upper_bound(all(vert[x]), y); it != vert[x].end(); ++it) {
        ret.push_back({x, *it});
      }
    }
    return ret;
  };

  N = n+1;
  for (int i = 0; i <= N; i++) bit[i] = new SegDyn(0, N);
  for (auto [x, y]: ps) {
    add(x, y, 1);
  }

  auto calc_trans = [&](int i, int x, int y) -> int {
    int ret = dp[y];
    // add all points in the rectangle [i, y) X [0, i]
    ret += getRangeSum(i, y-1, 0, i);
    /*
       for (int xx = i; xx < y; xx++) {
       if (!vert[xx].empty()) {
       ret += distance(vert[xx].begin(), upper_bound(all(vert[xx]), i));
       }
       }
       */
    if (x < y) ret++;
    return ret;
  };

  for (int i = n-1; i >= d; i--) {
    if (vert.count(i)) {
      for (auto y: vert[i]) {
        horiz[y].push_front(i);
      }
    }
    if (i != d && !hasy[i]) continue;
    auto [x, y] = next_point(i);
    // cout << i << ": " << x << ' ' << y << endl;
    ckmax(dp[i], calc_trans(i, x, y));
    for (auto [xx, yy]: get_between(i, y)) {
      ckmax(dp[i], calc_trans(i, xx, yy));
    }
    // cout << i << ": " << dp[i] << endl;
  }

  return dp[d];
}

// For each point (x, x) on the line y = x, find the "next" point with strictly higher y-coordinate, and least possible x-coordinate, call this (x', y')
// Check transitioning to this point, and all points "in between" (with x-coordinate in the range [x, y'), and y-coordinate > y')

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, d; cin >> n >> d;
  vector<array<int,2>> points;
  set<int> s; s.insert(d);
  map<int, int> compress;
  for (int i = 0; i < n; i++) {
    int x, y; cin >> x >> y;
    points.push_back({x, y});
    s.insert(x);
    s.insert(y);
  }
  int pt = 0;
  for (int i: s) {
    compress[i] = pt++;
  }
  d = compress[d];
  for (int i = 0; i < sz(points); i++) {
    points[i] = {compress[points[i][0]], compress[points[i][1]]};
  }

  int ans = solve(points, pt, d);
  cout << ans << '\n';
}
