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

int sub(int x) {
  cout << "- " << x << endl;
  int i; cin >> i;
  return i;
}
int add(int x) {
  cout << "+ " << x << endl;
  int i; cin >> i;
  return i;
}

void answer(int n) {
  cout << "! " << n << endl;
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int K = 250;
  int x; cin >> x;
  vector<int> v = {x};
  map<int, int> S; S[x] = 0;
  F0R(i, K-1) {
    x = add(1);
    if (S.count(x)) {
      answer(sz(S));
    }
    v.push_back(x);
    S[x] = i+1;
  }
  assert(sz(v) == K);
  int mx = S.rbegin()->first;
  int sum = K-1;
  REP(500) {
    const int M = 1e6;
    int r = rng() % M + 1;
    sum += r;
    x = add(r);
    ckmax(mx, x);
  }
  int n = mx;
  if (sum > (n-1)) sub(sum - (n-1));
  else if (sum < (n-1)) add((n-1) - sum);
  while (1) {
    x = add(K);
    n += K;
    if (S.count(x)) {
      n -= S[x]+1;
      answer(n);
    }
  }
}
