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

const int maxn = 505;
int N, K;
int A[maxn][maxn];

struct Tracker {
  vector<int> cnt;
  int distinct = 0;

  Tracker() {
    cnt.resize(N*N+1, 0);
    F0R(i, N) {
      F0R(j, N) {
        add(A[i][j]);
      }
    }
  }

  void sub(int i) {
    if (--cnt[i] == 0) distinct--;
  }
  void add(int i) {
    if (cnt[i]++ == 0) distinct++;
  }

  bool valid() {
    return distinct == K || distinct + 1 == K;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A[i][j];
    }
  }
  Tracker init_tracker;
  if (init_tracker.distinct <= K) {
    cout << K - init_tracker.distinct << '\n';
    return 0;
  }

  bool can_do_1 = false;
  for (int s = 1; s <= N; s++) {
    Tracker tracker;
    for (int i = 0; i+s <= N; i++) {
      for (int ii = i; ii < i+s; ii++) {
        for (int j = 0; j < s; j++) {
          tracker.sub(A[j][ii]);
        }
      }
      if (tracker.valid()) {
        can_do_1 = true;
        goto done;
      }
      for (int j = s; j < N; j++) {
        for (int ii = i; ii < i+s; ii++) {
          tracker.sub(A[j][ii]);
        }
        for (int ii = i; ii < i+s; ii++) {
          tracker.add(A[j-s][ii]);
        }
        if (tracker.valid()) {
          can_do_1 = true;
          goto done;
        }
      }

      // reset
      for (int j = N-s; j < N; j++) {
        for (int ii = i; ii < i+s; ii++) {
          tracker.add(A[j][ii]);
        }
      }
    }
  }

  done:;

  if (can_do_1) {
    cout << 1 << '\n';
  }
  else {
    cout << 2 << '\n';
  }
}
