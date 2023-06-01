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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> B(N);
  F0R(i, N) cin >> B[i];

  if (*min_element(all(B)) == *max_element(all(B))) {
    if (B[0] == 0) {
      cout << "YES\n";
      F0R(i, N) cout << 1 << ' ';
      cout << '\n';
    }
    else {
      cout << "NO\n";
    }
  }
  else {
    auto ceil = [&](ll a, ll b) {
      return (a + b - 1) / b;
    };
    vector<ll> A(N);
    F0R(i, N) {
      if (B[i] > B[(i-1+N)%N]) {
        int j = i;
        while (!A[j] && B[j] > B[(j-1+N)%N]) {
          A[j] = B[j];
          j = (j + 1) % N;
        }
        j = (i-1+N)%N;
        const int M = 1e6;
        while (!A[j] && B[j] <= B[(j-1+N)%N]) {
          A[j] = B[j] + A[(j+1)%N] * ceil(M-B[j], A[(j+1)%N]);
          j = (j - 1 + N) % N;
        }
      }
    }

    cout << "YES\n";
    F0R(i, N) {
      cout << A[i] << ' ';
    }
    cout << endl;

    F0R(i, N) {
      assert(A[i]);
      assert(A[i] % A[(i+1)%N] == B[i]);
    }
  }
}
