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

const int maxn = 1e5+5;
int N, A[maxn];
struct Tracker {
  int d = 0;
  vector<int> cnt;
  Tracker() { cnt.resize(N+1); }
  inline bool canadd(int x, int K) { return (cnt[x] > 0 && d <= K) || d+1 <= K; }
  inline void add(int x) { if (cnt[x]++ == 0) d++; }
  inline void remove(int x) { if (--cnt[x] == 0) d--; }
};

int ans[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
  }

  const int MAGIC = 1000;
  FOR(k, 1, min(MAGIC, N)+1) {
    Tracker tracker;
    ans[k] = 1;
    for (int i = 0, j = 0; i < N; i++) {
      if (tracker.canadd(A[i], k)) {
        tracker.add(A[i]);
      }
      else {
        while (j < i) tracker.remove(A[j++]);
        tracker.add(A[i]);
        ans[k]++;
      }
    }
  }

  list<tuple<int, int, Tracker>> ls;
  {
    // initialize ls
    int l = 0, r = 0;
    Tracker tracker;
    while (r < N) {
      if (tracker.canadd(A[r], MAGIC)) {
        tracker.add(A[r++]);
      }
      else {
        ls.push_back({l, r-1, tracker});
        l = r;
        tracker = Tracker();
        tracker.add(A[r++]);
      }
    }
    ls.push_back({l, N-1, tracker});
  }

  FOR(k, MAGIC+1, N+1) {
    int cur_r = -1;
    for (auto it = ls.begin(); it != ls.end();) {
      auto& [l, r, tracker] = *it;
      if (r <= cur_r) {
        it = ls.erase(it);
      }
      else {
        while (l <= cur_r) tracker.remove(A[l++]);
        while (r+1 < N && tracker.canadd(A[r+1], k)) {
          tracker.add(A[++r]);
        }
        cur_r = r;
        ++it;
      }
    }
    ans[k] = sz(ls);
  }

  FOR(i, 1, N+1) {
    cout << ans[i] << " \n"[i==N];
  }
}
