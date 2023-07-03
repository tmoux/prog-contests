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

// 11111...110 always 0
// ends in 1, always can be 1
// If ends in 1, can NOT be 0
// If at least 2 0's, and one at the end:
// 111101110
// Can always be 0
// Can always be 1: 0 -> (1 -> 1 -> ... -> 0) = 0 -> 0 = 1, now ends in 1
// Need right to be a 0, must end in 0
// Need left to end in a 1
// If no end in 1: 0000, ((0 -> 0) -> 0) 0 = (1 -> 0) -> 0
// (0 -> 0) -> 0
// If there is a 1: then find the last one

// (0 -> (0 -> (0 -> 0)))
// 0 -> 0 -> 0
// 0 -> 0 -> 0 -> 0
// 1 1 0 0 -> 0 1 0 0

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  auto solve = [&](int l, int r) -> string {
    int k = r-l+1;
    string ans(k, '(');
    for (int i = l; i <= r; i++) {
      if (i > l) ans += "->";
      ans += A[i] + '0';
      ans += ')';
    }
    return ans;
  };
  auto solve2 = [&](int l, int r) -> string {
    string ans = "(";
    for (int i = l; i <= r; i++) {
      if (i > l) ans += "->";
      ans += A[i] + '0';
    }
    ans += ")";
    return ans;
  };
  if (A[N-1] == 1) {
    cout << "NO\n";
  }
  else if (N >= 2 && A[N-1] == 0 && A[N-2] == 0 && std::accumulate(all(A), 0) == N-2) {
    cout << "NO\n";
  }
  else {
    cout << "YES\n";
    if (N == 1) {
      cout << 0 << '\n';
    }
    else if (A[N-2] == 1) {
      F0R(i, N) {
        if (i > 0) cout << "->";
        cout << (char)(A[i]+'0');
      }
      cout << '\n';
    }
    else if (N >= 3 && A[N-1] == 0 && A[N-2] == 0 && A[N-3] == 0) {
      cout << "(";
      F0R(i, N) {
        if (i > 0) cout << "->";
        if (i == N-3) cout << "(";
        cout << (char)(A[i]+'0');
        if (i == N-2) cout << "))";
      }
      cout << '\n';
    }
    else {
      int j = N-2;
      while (A[j] == 0) j--;
      int k = j;
      while (A[k] == 1) k--;
      for (int i = 0; i < k; i++) {
        if (i > 0) cout << "->";
        cout << (char)(A[i]+'0');
      }
      if (k > 0) cout << "->";
      cout << "(0->(";
      for (int i = k+1; i < N-1; i++) {
        if (i > k+1) cout << "->";
        cout << (char)(A[i]+'0');
      }
      cout << "))";
      cout << "->0" << '\n';
    }
  }
}
