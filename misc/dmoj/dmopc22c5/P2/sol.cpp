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

int N;
int check(vector<ll> A) {
  int X = 0, Y = 0;
  F0R(i, N) {
    ll sum = 0;
    FOR(j, i, N) {
      sum += A[j];
      (sum >= 0 ? X : Y)++;
    }
  }
  // cout << X << ' ' << Y << ' ' << abs(X - Y) << endl;
  return abs(X - Y);
}

vector<ll> v;
pair<int, vector<int>> best = {1000000000, {}};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  ll target = 1LL * N * (N + 1) / 2 / 2;
  v.resize(N, -1);
  int i = 0;
  auto c2 = [&](int n) {
    return 1LL * n * (n - 1) / 2;
  };

  int cur = 2*N;
  while (target > 0 && i < N) {
    int j = i;
    while (j < N && c2(j-i+1)+(j-i+1) <= target) {
      v[j] = cur;
      j++;
    }
    target -= c2(j-i)+(j-i);
    i = j;
    cur--;
  }
  cur = -1;
  while (i < N) {
    v[i++] = cur;
    cur--;
  }

  // F0R(i, N) {
  //   cout << v[i] << " \n"[i == N-1];
  // }
  F0Rd(i, N) {
    v[i] = i == 0 ? v[i] : v[i] - v[i-1];
  }
  // cout << target << endl;

  // cout << check(v) << endl;

  F0R(i, N) {
    cout << v[i] << " \n"[i == N-1];
  }
  // vector<int> A(N);
  // F0R(i, N) {
  //   A[i] = (i % 2 == 0 ? 1 : -1) * (N - i);
  // }
  // cout << A << endl;

}
