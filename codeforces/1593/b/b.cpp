#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

/* requires c++20
template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};
*/

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) //requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;

    auto has_subseq = [&](char c1, char c2) {
      int ans = sz(s);
      for (int i = 0; i < sz(s); i++) {
        if (s[i] == c1) {
          for (int j = i+1; j < sz(s); j++) {
            if (s[j] == c2) {
              ckmin(ans, sz(s) - 2 - i);
            }
          }
        }
      }
      return ans;
    };

    int ans = sz(s);
    ckmin(ans, has_subseq('0','0'));
    ckmin(ans, has_subseq('2','5'));
    ckmin(ans, has_subseq('5','0'));
    ckmin(ans, has_subseq('7','5'));

    assert(ans != sz(s));
    cout << ans << '\n';
  }
}
