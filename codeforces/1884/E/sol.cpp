#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

namespace ModInt {
  template<int MOD>
  struct mod_int {
    int val;

    operator int() const { return val; }
    mod_int() : val(0) {}
    mod_int(ll _val) : val((_val + MOD) % MOD) {}

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

    mod_int& operator+=(int b) {
      return *this += mod_int(b);
    }
    mod_int& operator-=(int b) {
      return *this -= mod_int(b);
    }
    mod_int& operator*=(int b) {
      return *this *= mod_int(b);
    }
    mod_int& operator/=(int b) {
      return *this /= mod_int(b);
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

    friend mod_int operator+(const mod_int& a, int b) {
      return a + mod_int(b);
    }
    friend mod_int operator-(const mod_int& a, int b) {
      return a - mod_int(b);
    }
    friend mod_int operator*(const mod_int& a, int b) {
      return a * mod_int(b);
    }
    friend mod_int operator/(const mod_int& a, int b) {
      return a / mod_int(b);
    }
    friend mod_int operator+(int a, const mod_int& b) {
      return mod_int(a) + b;
    }
    friend mod_int operator-(int a, const mod_int& b) {
      return mod_int(a) - b;
    }
    friend mod_int operator*(int a, const mod_int& b) {
      return mod_int(a) * b;
    }
    friend mod_int operator/(int a, const mod_int& b) {
      return mod_int(a) / b;
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
      return i >> x.val;
    }
  };
}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

using T = pair<ll, mint>;
T& operator+=(T& a, const T& b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

struct Tracker {
  vector<array<int, 4>> st; // ai, x, i, exL
  mint curCost = 0;
  mint delta = 0;
  mint d_delta = 0;

  void insert(int ai, int i) {
    while (!st.empty() && st.back()[0] >= ai) {
      auto [aj, xj, j, exL] = st.back(); st.pop_back();
      d_delta -= 2 * xj;
      int l = i - j + exL;
      delta -= mint(xj) * (2 * l + 1);
    }
    int x = ai - (st.empty() ? 0 : st.back()[0]);

    int L = i - (st.empty() ? 0 : st.back()[2]+1);
    st.push_back({ai, x, i, L});
    d_delta += 2 * x;
    delta += mint(x) * (2 * L + 1);
    curCost += delta;
    delta += d_delta;
  }

  mint getCost() const {
    return curCost;
  }
};

vector<T> computePrefix(vector<int> A) {
  int N = sz(A);
  vector<T> ans(N);
  Tracker tracker;
  ll ops = 0;
  F0R(i, N) {
    if (i == 0 || A[i] > A[i-1]) {
      ops += i == 0 ? A[i] : A[i] - A[i-1];
    }
    int x = A[i];
    tracker.insert(x, i);
    ans[i] = {ops, tracker.getCost()};
  }
  return ans;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  pair<int, int> mx = {-1, -1};
  F0R(i, N) ckmax(mx, {A[i], i});
  F0R(i, N) A[i] = mx.first - A[i];
  int shift = mx.second;
  rotate(A.begin(), A.begin() + shift, A.end());
  // Assume mx is at the front

  vector<T> Left = computePrefix(A);
  auto AR = A; reverse(all(AR));
  vector<T> Right = computePrefix(AR);
  reverse(all(Right));

  vector<T> ans(N, {0, 0});
  F0R(i, N) {
    if (i > 0) ans[i] += Left[i-1];
    ans[i] += Right[i];
  }

  rotate(ans.begin(), ans.begin() + (N - shift), ans.end());
  for (auto [a, b]: ans) {
    cout << a << ' '  << b << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
