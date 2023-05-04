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

class Tracker {
  private:
    int m;
    map<int, int> S, T;

    void fix() {
      if (T.empty()) return;
      if (S.rbegin()->first == T.rbegin()->first + 1 && S.rbegin()->second == 1 && T.rbegin()->second == m-1) {
        int i = T.rbegin()->first;
        S.erase(prev(S.end()));
        T.erase(prev(T.end()));
        add(i);
      }
    }
  public:
    Tracker(int _m) : m(_m) {}
    void add(int i) {
      if (T.count(i)) {
        if (T[i] == 1) T.erase(i);
        else T[i]--;
      }
      else if (S[i] + 1 < m) {
        S[i]++;
      }
      else {
        assert(S[i] == m-1);
        S.erase(i);
        add(i+1);
      }
      fix();
    }

    void sub(int i) {
      if (S.count(i)) {
        if (S[i] == 1) S.erase(i);
        else S[i]--;
      }
      else if (T[i] + 1 < m) {
        T[i]++;
      }
      else {
        assert(T[i] == m-1);
        T.erase(i);
        sub(i+1);
      }
      fix();
    }

    int getHighestBit() {
      assert(!S.empty());
      int i = S.rbegin()->first;
      if (T.empty()) return i;
      else {
        int j = T.rbegin()->first;
        if (S[i] == 1 && (sz(S) == 1 || next(S.rbegin())->first < j)) return i-1;
        else return i;
      }
    }
};

void solve() {
  int N, Q; cin >> N >> Q;
  vector<int> A(N);
  Tracker tracker(2);
  F0R(i, N) {
    cin >> A[i];
    tracker.add(A[i]);
  }

  while (Q--) {
    int i, x; cin >> i >> x;
    i--;
    tracker.sub(A[i]);
    A[i] = x;
    tracker.add(A[i]);
    cout << tracker.getHighestBit() << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T = 1;
  while (T--) solve();
}
