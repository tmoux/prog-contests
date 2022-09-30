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

bool good(int x) {
  while (x > 0) {
    if (x % 3 == 2) return false;
    x /= 3;
  }
  return true;
}

inline int positive_mod(int i, int n) {
  return (i % n + n) % n;
}

vector<ll> solve(int N, ll M) {
  vector<ll> ans;
  ll sum = 0;
  for (int x = 0; sz(ans) < N; x += 2) {
    if (good(x)) {
      ans.push_back(x);
      sum += x;
    }
  }

  F0R(i, N) {
    if ((M - sum) % N == 0) {
      break;
    }
    else {
      ans[i]++;
      sum++;
    }
  }

  ll add = (M - sum)/N;
  F0R(i, N) {
    ans[i] += add;
    sum += add;
  }
  // assert(sum == M);
  assert(accumulate(all(ans), 0LL) == M);

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  ll M; cin >> M;

  if (M < 0) {
    auto ans = solve(N, -M);
    for (auto& x: ans) x *= -1;
    F0R(i, N) {
      cout << ans[i] << " \n"[i==N-1];
    }
  }
  else {
    auto ans = solve(N, M);
    F0R(i, N) {
      cout << ans[i] << " \n"[i==N-1];
    }
  }
}
