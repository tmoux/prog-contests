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

  template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v)
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

vector<int> v;
vector<int> ans;
bool done;
void rec(int i, int last, int len, int k) {
  if (done) return;
  if (i == len) {
    bool poss = true;
    for (int j = 1; j + 1 < v.size(); j++) {
      if (v[j-1] + v[j+1] >= 2*v[j]) poss = false;
    }
    if (poss) {
      ans = v;
      done = true;
    }
  }
  else {
    for (int d = last-1; d >= 1; d--) {
      v.push_back(d);
      rec(i+1, d, len, k);
      v.pop_back();
    }
  }
}

bool generate(int len, int k) {
  v = {k};
  ans.clear();
  done = false;
  rec(1, k, len, k);
  return done;
}

void brute(int k) {
  for (int len = k; len >= 0; len--) {
    if (generate(len, k)) {
      cout << k << ": " << sz(ans) << ": ";
      cout << ans << '\n';
      return;
    }
  }
  cout << k << ": " << "impossible\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int k = 2; k <= 23; k++) {
    brute(k);
  }
}
