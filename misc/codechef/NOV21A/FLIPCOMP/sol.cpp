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

// }}}

int solve(string S) {
  auto calc = [](string s) {
    int ans = 0;
    for (int i = 0; i < sz(s); i++) {
      if (s[i] == '1' && (i == 0 || s[i-1] == '0') && (i == sz(s) - 1 || s[i+1] == '0')) {
        //isolated 1, flip it and add 1 to the answer
        s[i] = '0';
        ans++;
      }
      else if (i > 0 && i + 1 < sz(s) && s[i] == '0' && s[i-1] == '1' && s[i+1] == '1') {
        //isolated 0, flip it and add 1 to the answer
        s[i] = '1';
        ans++;
      }
    }
    for (int i = 0; i < sz(s); i++) {
      if (s[i] == '1' && (i == 0 || s[i-1] == '0')) {
        assert(s[i+1] == '1');
        ans += 2;
      }
    }
    return ans;
  };

  int ret = calc(S);
  for (auto& c: S) c = c == '0' ? '1' : '0';
  ckmin(ret, calc(S));
  return ret;
}

int brute(string S) {
  vector<int> v;
  char cur = S[0];
  int num = 0;
  for (int i = 0; i < sz(S); i++) {
    if (S[i] == cur) {
      num++;
    }
    else {
      v.push_back(num);
      cur = S[i];
      num = 1;
    }
  }
  if (num > 0) v.push_back(num);

  auto calc = y_combinator([](auto calc, vector<int> v) -> int {
    if (sz(v) <= 1) return 0;
    //try compressing a segment
    int ans = 2 * sz(v);
    for (int i = 0; i < sz(v); i++) {
      if (v[i] > 1) {
        auto u = v;
        u[i] = 1;
        ckmin(ans, calc(u) + 1);
      }
    }
    //try flipping a 1
    for (int i = 0; i < sz(v); i++) {
      if (v[i] == 1) {
        vector<int> u;
        for (int j = 0; j < i-1; j++) {
          u.push_back(v[j]);
        }
        int x = v[i];
        if (i-1 >= 0) x += v[i-1];
        if (i+1 < sz(v)) x += v[i+1];
        u.push_back(x);
        for (int j = i+2; j < sz(v); j++) {
          u.push_back(v[j]);
        }

        ckmin(ans, calc(u) + 1);
      }
    }
    return ans;
  });

  return calc(v);

  /*
  for (auto i: v) {
    cout << i << ' ';
  }
  cout << '\n';
  */

  return 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    string S; cin >> S;
    int my = solve(S);
    cout << my << '\n';
    // int b = brute(S);
    // cout << my << ' ' << b << endl;
    // assert(my == b);
    //cout << solve(S) << '\n';
    //cout << brute(S) << '\n';
  }
}
