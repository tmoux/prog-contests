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

const int maxn = 70000;
struct Tracker {
  bitset<maxn> msk;
  map<int, int> cnt;
  int offset = 0;
  int end;

  Tracker(string t) {
    int cur = N;
    for (char c: t) {
      if (c == 'L') cur--;
      else if (c == 'R') cur++;
      else if (c == 'T') {
        add(cur);
      }
      else assert(false);
    }
    end = cur;
  }

  void rem(int i) {
    // cout << "removing " << i << endl;
    assert(cnt.count(i));
    if (--cnt[i] == 0) msk[i] = 0;
  }

  void add(int i) {
    // cout << "adding " << i << endl;
    if (++cnt[i] == 1) msk[i] = 1;
  }

  void addL() {
    // cout << "add L " << endl;
    offset--;
  }

  void addR() {
    offset++;
  }

  void addT() {
    int end_n = end - offset;
    rem(end_n);
    add(N-offset);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  bitset<maxn> mask;
  string s; cin >> s;
  F0R(i, 2*N+1) mask[i] = s[i]-'0';
  string t; cin >> t;
  Tracker tracker(t);

  int ans = 0;

  F0Rd(i, N) {
    if (t[i] == 'L') tracker.addL();
    else if (t[i] == 'R') tracker.addR();
    else if (t[i] == 'T') tracker.addT();
    else assert(false);

    bitset<maxn> m = tracker.offset < 0 ?
      tracker.msk >> (-tracker.offset) :
      tracker.msk << tracker.offset;
    int c = (m & mask).count();
    ckmax(ans, c);

    /*
    cout << i << ": ";
    F0R(j, 7) cout << m[j];
    cout << '\n';
    cout << i << ": " << c << endl;
    */
  }

  cout << ans << '\n';
}
