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

struct Tracker {
  int N;
  vector<int> A;
  multiset<int> ms, s;

  Tracker(int _N, vector<int> _A) {
    N = _N;
    A = _A;
    for (int i = 0; i + 1 < N; i++) {
      ms.insert(min(A[i], A[i+1]));
    }
    F0R(i, N) s.insert(A[i]);
  }

  void update(int i, int x) {
    if (i > 0) {
      auto it = ms.find(min(A[i], A[i-1]));
      ms.erase(it);
    }
    if (i+1 < N) {
      auto it = ms.find(min(A[i], A[i+1]));
      ms.erase(it);
    }

    auto it = s.find(A[i]);
    s.erase(it);

    A[i] = x;

    if (i > 0) {
      ms.insert(min(A[i], A[i-1]));
    }
    if (i+1 < N) {
      ms.insert(min(A[i], A[i+1]));
    }

    s.insert(A[i]);
  }

  int max_pair() {
    return *ms.rbegin();
  }

  int max_val() {
    return *s.rbegin();
  }
};

int solve() {
  int N, K; cin >> N >> K;
  vector<int> A(N);
  map<int, vector<int>> pos;
  F0R(i, N) {
    cin >> A[i];
    pos[A[i]].push_back(i);
  }
  Tracker tracker(N, A);

  const int MX = 1000000000;
  auto get_ans = [&](int mn) {
    if (K == 0) {
      return min(2*mn, tracker.max_pair());
    }
    else if (K == 1) {
      return min(2*mn, max(tracker.max_pair(), tracker.max_val()));
    }
    else {
      return min(2*mn, MX);
    }
  };
  int ans = 0;
  for (auto [x, v]: pos) {
    if (K < 0) break;
    ckmax(ans, get_ans(x));
    for (int i: v) {
      tracker.update(i, MX);
      if (x < MX) K--;
    }
  }
  if (K >= 0) ckmax(ans, get_ans(MX));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
