#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

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

const ld PI = atan(1)*4;
int N;
struct Point
{
    ld x, y;
    ld angle;
};
vector<Point> pts;

Point add(Point a, Point b) {
  return {a.x+b.x,a.y+b.y};
}

Point sub(Point a, Point b) {
  return {a.x-b.x,a.y-b.y};
}

ld mag(Point a) {
  return 1LL*a.x*a.x + 1LL*a.y*a.y;
}

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 0; i < N; i++) {
    string a, b, c, d; cin >> a >> b >> c >> d;
    ld xi = stod(a) - stod(b);
    ld yi = stod(c) - stod(d);
    if (xi == 0 && yi == 0) {
      continue;
    }
    else {
      pts.push_back({xi,yi,atan2(xi,yi)});
    }
  }
  N = pts.size();
  sort(pts.begin(),pts.end(),[](Point a, Point b) {
    return a.angle < b.angle;
  });
  for (int i = 0; i < N; i++) {
    pts.push_back({pts[i].x,pts[i].y,pts[i].angle+2*PI});
  }

  ld res = 0;
  Point sum = {0,0};
  int j = 0;
  for (int i = 0; i < N; i++) {
    if (i > 0) {
      sum = sub(sum,pts[i-1]);
    }
    res = max(res,mag(sum));
    while (j < sz(pts) && pts[j].angle < pts[i].angle + PI) {
      sum = add(sum,pts[j]);
      res = max(res,mag(sum));
      j++;
    }
    ckmax(res, mag(sum));
  }
  cout << fixed << setprecision(10) << res << '\n';
}
