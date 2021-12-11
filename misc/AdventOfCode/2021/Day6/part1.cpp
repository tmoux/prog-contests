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

  template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 256;
  vector<ll> orig(9);
  int x;
  while (cin >> x) {
    orig[x]++;
  }
  F0R(i, T) {
    vector<ll> news(9);
    news[0] = orig[1];
    news[1] = orig[2];
    news[2] = orig[3];
    news[3] = orig[4];
    news[4] = orig[5];
    news[5] = orig[6];
    news[6] = orig[7] + orig[0];
    news[7] = orig[8];
    news[8] = orig[0];

    orig = news;

    cout << orig << endl;
    /*
    rotate(orig.begin(), orig.begin()+1, orig.end());
    rotate(news.begin(), news.begin()+1, news.end());

    cout << orig << endl;
    cout << news << endl;
    */
    ll ans = 0;
    for (auto i: orig) ans += i;
    cout << i << ": " << ans << endl;
  }


  ll ans = 0;
  for (auto i: orig) ans += i;
  cout << ans << '\n';
}
