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

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

      mod_int() : val(0) {}
      mod_int(int _val) : val(_val % MOD) {}

      mod_int operator+() const {
        return mod_int(val); 
      }
      mod_int operator-() const {
        return mod_int(MOD-val); 
      }
      mod_int inverse() const {
        assert(val != 0);
        return *this ^ (MOD - 2);
      }

      bool operator==(const mod_int& b) const {
        return val == b.val;
      }

      bool operator!=(const mod_int& b) const {
        return !(*this == b);
      }

      mod_int& operator+=(const mod_int& b) {
        val += b.val;
        if (val >= MOD) val -= MOD;
        return *this;
      }
      mod_int& operator-=(const mod_int& b) {
        return *this += -b;
      }
      mod_int& operator*=(const mod_int& b) {
        val = (1LL*val*b.val) % MOD;
        return *this;
      }
      mod_int& operator/=(const mod_int& b) {
        val = (1LL*val*b.inverse().val) % MOD;
        return *this;
      }

      mod_int& operator++(int) {
        return *this += 1;
      }

      mod_int& operator--(int) {
        return *this -= 1;
      }

      friend mod_int operator+(const mod_int& a, const mod_int& b) {
        mod_int c = a; c += b;
        return c;
      }
      friend mod_int operator-(const mod_int& a, const mod_int& b) {
        mod_int c = a; c -= b;
        return c;
      }
      friend mod_int operator*(const mod_int& a, const mod_int& b) {
        mod_int c = a; c *= b;
        return c;
      }
      friend mod_int operator/(const mod_int& a, const mod_int& b) {
        mod_int c = a; c /= b;
        return c;
      }

      friend mod_int operator^(mod_int a, int b) {
        mod_int res(1);
        while (b > 0) {
          if (b&1) res *= a;
          a *= a;
          b >>= 1;
        }
        return res;
      }

      friend ostream& operator<<(ostream& o, const mod_int& x) {
        return o << x.val;
      };
      friend istream& operator>>(istream& i, mod_int& x) {
        i >> x.val; x.val %= MOD;
        return i;
      }
    };
} 
//}}}
const int MOD = 998244353;
using mint = ModInt::mod_int<MOD>;

int get(int par, int cnt) {
  return par == -1 ? -cnt-1 : cnt;
}

int cv(int a) {
  if (a < 0) {
    if (a == -1) return MOD - 1;
    else if (a == -2) return MOD - 2;
    else assert(false);
  }
  else {
    mint x = mint(2) ^ a;
    return x.val;
  }
}

int solve() {
  int N; cin >> N;
  vector<int> v(N);
  bool has_0 = false;
  F0R(i, N) {
    cin >> v[i];
    if (v[i] == 0) has_0 = true;
  }

  auto rec = y_combinator([&](auto rec, int L, int R) -> int {
    int M = (L+R)/2;
    int par = 1;
    int cnt = 0;
    map<int, int> mp;

    int mn = 2e9;
    for (int i = M; i >= L; i--) {
      if (v[i] == 0) break;
      else {
        if (v[i] < 0)  par *= -1;
        if (abs(v[i]) == 2) cnt++;
        ckmax(mp[par], cnt);
        if (par == -1) ckmin(mn, cnt);
      }
    }

    par = 1;
    cnt = 0;

    int best = mp.count(1) ? mp[1] : get(-1, mn);
    for (int i = M+1; i <= R; i++) {
      if (v[i] == 0) break;
      else {
        if (v[i] < 0)  par *= -1;
        if (abs(v[i]) == 2) cnt++;

        ckmax(best, get(par, cnt));

        if (mp.count(1)) {
          ckmax(best, get(par, cnt + mp[1]));
        }
        if (mp.count(-1)) {
          ckmax(best, get(-par, cnt + mp[-1]));
        }
      }
    }
    // cout << mp << endl;
    // cout << L << ' ' << R << ": " << best << endl;
    if (L < R) {
      ckmax(best, rec(L, M));
      ckmax(best, rec(M+1, R));
    }
    return best;
  });

  int best = rec(0, N-1);
  if (best < 0 && has_0) {
    return 0;
  }
  else {
    // DEBUG(best);
    return cv(best);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
