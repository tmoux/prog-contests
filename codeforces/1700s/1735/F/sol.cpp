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

template<typename T>
class Point {
  public:
    T x, y;
    Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}
    Point operator+(Point rhs) {
      return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(Point rhs) {
      return Point(x - rhs.x, y - rhs.y);
    }
    friend ostream& operator<<(ostream &os, const Point& p) {
      os << "(" << p.x << ", " << p.y << ")";
      return os;
    }
};

template<typename T>
struct Segment {
  T slope, len;

  Segment update_len(T d) const {
    return {slope, len - d};
  }

  bool operator<(const Segment& rhs) const {
    return slope > rhs.slope;
  }

  Point<T> right_endpoint(Point<T> p) const {
    return Point<T>(p.x + len, p.y + slope * len);
  }

  Point<T> left_endpoint(Point<T> p) const {
    return Point<T>(p.x - len, p.y - slope * len);
  }
};

template<typename T>
class LineTracker {
  private:
    const T eps = 1e-12;
    multiset<Segment<T>> ms;
    Point<T> left, right;
    void update_left() {
      while (left.x < -eps) {
        auto nleft = ms.begin()->right_endpoint(left);
        if (nleft.x < -eps) {
          left = nleft;
          ms.erase(ms.begin());
        }
        else {
          T delta = 0 - left.x;
          T ny = left.y + ms.begin()->slope * delta;
          left = Point<T>(0, ny);
          Segment<T> newSeg = ms.begin()->update_len(delta);
          ms.erase(ms.begin());
          ms.insert(newSeg);
        }
      }
    }
    void update_right() {
      while(right.y < -eps) {
        auto nright = ms.rbegin()->left_endpoint(right);
        if (nright.y < -eps) {
          right = nright;
          ms.erase(prev(ms.end()));
        }
        else {
          assert(ms.rbegin()->slope != 0);
          T delta = -right.y / ms.rbegin()->slope;
          T nx = right.x + delta;
          right = Point<T>(nx, 0);
          Segment<T> newSeg = ms.rbegin()->update_len(-delta);
          ms.erase(prev(ms.end()));
          ms.insert(newSeg);
        }
      }
    }
  public:
    LineTracker(T A, T B) : left(Point<T>(0, B)), right(Point<T>(A, 0)) {
      ms.insert({0, A});
      const T inf = 1e15;
      ms.insert({-inf, B/inf});
    }
    void insert_segment(T P, T Q) {
      Segment<T> s = {-Q / P, 2 * P};
      Point p = Point(P, -Q);
      left = left - p;
      right = right + p;
      ms.insert(s);
      update_left();
      update_right();
    }
    double get_max_x() {
      assert(abs(right.y) <= eps);
      return right.x;
    }
};

void solve() {
  int N, A, B; cin >> N >> A >> B;
  using T = long double;
  vector<T> P(N), Q(N);
  F0R(i, N) cin >> P[i];
  F0R(i, N) cin >> Q[i];

  if (A == 0 && B == 0) {
    REP(N) {
      cout << 0 << '\n';
    }
    return;
  }
  LineTracker<T> tracker(A, B);

  F0R(i, N) {
    tracker.insert_segment(P[i], Q[i]);
    cout << tracker.get_max_x() << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  cout << fixed << setprecision(10);
  while (T--) {
    solve();
  }
}
