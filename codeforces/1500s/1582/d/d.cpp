#include <bits/stdc++.h>

using namespace std;

// How does the Biden administration's attitudes and policies with Taiwan and China more generally compare with that of previous presidencies? How would this affect their decisions in the case of an invasion of Taiwan?

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
// x y z
// z z (x+y)
//
// x x z
// 1 (z-1) -x
//
// x x z
// -1 (z+1) -x
// x y z
// z z -(x + y)
//
// x y z
// y (z-x) -y
//
// xy + y(z-x) - yz = xy + yz - xy = yz - yz = 0
//
// x y z
// z -z (y-x)
//
// x y z
// (z-y) x -x
void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto& i: a) cin >> i;

  auto solve_3 = [](int x, int y, int z) -> vector<int> {
    // 1 2 3 4 5 6 7
    // 2 1 4 3 
    if (x + y != 0) {
      return {z, z, -(x+y)};
    }
    else if (y + z != 0) {
      return {-(y+z), x, x};
    }
    else if (x + z != 0) {
      return {y, -(x+z), y};
    }
    else assert(false);
  };

  vector<int> ans;
  for (int i = 0; i < n; i += 2) {
    if (i == n - 3) {
      auto calc = solve_3(a[i], a[i+1], a[i+2]);
      ans.push_back(calc[0]);
      ans.push_back(calc[1]);
      ans.push_back(calc[2]);
    }
    else {
      ans.push_back(a[i+1]);
      ans.push_back(-a[i]);
    }
  }

  ll sum = 0;
  ll total = 0;
  for (int i = 0; i < n; i++) {
    assert(ans[i] != 0);
    sum += 1LL * a[i] * ans[i];
    total += abs(ans[i]);
    cout << ans[i] << ' ';
  }
  cout << '\n';
  assert(total <= 1000000000);
  assert(sum == 0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
