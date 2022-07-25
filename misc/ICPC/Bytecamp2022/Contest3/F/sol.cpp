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

const int maxn = 50;
ll fib[maxn];
string brute[maxn];

bool is_pal(int L, int R, int n);
bool is_prefix_match(int L, int R, int n);
bool is_suffix_match(int L, int R, int n);

int get_val(int i, int n) {
  // cout << "GET " << i << ": " << fib[n-1] << ' ' << n << endl;
  if (n == 0) {
    assert(i == 1);
    return 0;
  }
  else if (n == 1) {
    return i == 1 ? 0 : 1;
  }

  if (i <= fib[n-1]) {
    return get_val(i, n-1);
  }
  else {
    return get_val(i-fib[n-1], n-2);
  }
}

int calls = 0;

bool is_pal(int L, int R, int n) {
  calls++;
  // cout << "is pal " << L << ' ' << R << ' ' << n << endl;
  if (L > R) return true;
  if (L == R) return true;

  assert(n >= 0 && 1 <= L && L <= R && R <= fib[n]);

  if (n <= 2) {
    string s = brute[n].substr(L-1, R-L+1);
    string rev = s; reverse(all(rev));
    return s == rev;
  }


  if (R <= fib[n-1]) {
    return is_pal(L, R, n-1);
  }
  else if (L > fib[n-1]) {
    L -= fib[n-1];
    R -= fib[n-1];
    return is_pal(L, R, n-2);
  }
  else {
    int left_len = fib[n-1] - L + 1;
    int right_len = R - fib[n-1];
    if (left_len >= right_len) {
      return is_prefix_match(L, L+right_len-1, n-1) 
          && is_pal(L+right_len, fib[n-1], n-1);
    }
    else {
      return is_suffix_match(R-left_len+1-fib[n-1], R-fib[n-1], n-1)
          && is_pal(1, R-left_len-fib[n-1], n-2);
    }
  }
}

bool is_prefix_match(int L, int R, int n) {
  calls++;
  // cout << "is prefix " << L << ' ' << R << ' ' << n << endl;
  if (L > R) return true;
  if (L == R) {
    // must be 0
    return get_val(L, n) == get_val(1, n);
  }
  assert(n >= 0 && 1 <= L && L <= R && R <= fib[n]);

  if (n <= 2) {
    // brute force
    for (int i = L; i <= R; i++) {
      if (brute[n][i-1] != brute[n][R-L-(i-L)]) {
        return false;
      }
    }
    return true;
  }

  if (R <= fib[n-1]) {
    return is_prefix_match(L, R, n-1);
  }
  else if (L > fib[n-1]) {
    L -= fib[n-1];
    R -= fib[n-1];
    return is_prefix_match(L, R, n-2);
  }
  else {
    int right_len = R-fib[n-1];
    int total_len = R-L+1;
    // DEBUG(right_len);
    // DEBUG(total_len);
    return is_pal(1, R-fib[n-1], n-2)
        && is_suffix_match(right_len+1, total_len, n+1);
  }
}

bool is_suffix_match(int L, int R, int n) {
  calls++;
  // cout << "is suffix " << L << ' ' << R << ' ' << n << endl;
  if (L > R) return true;
  // if (L == R) return get_val(L, n) == get_val(fib[n], n);
  assert(n >= 0 && 1 <= L && L <= R && R <= fib[n]);
  if (n <= 2) {
    // brute force
    for (int i = L; i <= R; i++) {
      if (brute[n][i-1] != brute[n][sz(brute[n])-1-(i-L)]) {
        return false;
      }
    }
    return true;
  }

  if (L > fib[n-1]) {
    L -= fib[n-1];
    R -= fib[n-1];
    return is_suffix_match(L, R, n-2);
  }
  else if (L <= fib[n-2]) {
    if (R <= fib[n-2]) {
      return is_suffix_match(L, R, n-2);
    }
    if (R <= fib[n-1]) {
      return is_pal(L, fib[n-2], n-2)
          && is_prefix_match(fib[n]-(R-L), fib[n]-((fib[n-2]+1)-L), n);
    }
    else {
      return is_pal(L, fib[n-2], n-2)
          && is_prefix_match(fib[n]-(fib[n-1]-L), fib[n]-((fib[n-2]+1)-L), n)
          && is_prefix_match(fib[n]-(R-L), fib[n]-((fib[n-1]+1)-L), n);
    }
  }
  else {
    if (R <= fib[n-1]) {
      return is_suffix_match(L-fib[n-2], R-fib[n-2], n-2);
    }
    else {
      return is_suffix_match(L-fib[n-2], fib[n-1]-fib[n-2], n-2)
          && is_prefix_match(fib[n]-(R-L), fib[n]-(fib[n-1]+1-L), n);
    }
  }
}

bool query(int L, int R) {
  int n = 0;
  while (fib[n] < R) n++;
  return is_pal(L, R, n);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int N = 20;
  brute[0] = "0";
  brute[1] = "01";
  FOR(i, 2, N) {
    brute[i] = brute[i-1] + brute[i-2];
  }

  fib[0] = 1;
  fib[1] = 2;
  for (int i = 2; i < maxn; i++) {
    fib[i] = fib[i-1] + fib[i-2];
  }

  map<pair<int, int>, bool> mp;
  int Q; cin >> Q;
  while (Q--) {
    int L, len; cin >> L >> len;
    int R = L+len-1;
    bool ans = mp.count({L, R}) ? mp[{L, R}] : (mp[{L, R}] = query(L, R));
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
