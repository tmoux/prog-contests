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

deque<int> mergeLeft(deque<int> v, int i) {
  v.push_front(i);
  while (sz(v) >= 2 && v[0] == v[1]) {
    int x = v[0] + 1;
    v.pop_front();
    v.pop_front();
    v.push_front(x);
  }
  return v;
}

deque<int> mergeRight(deque<int> v, int i) {
  v.push_back(i);
  while (sz(v) >= 2 && v.back() == v[sz(v)-2]) {
    int x = v.back() + 1;
    v.pop_back();
    v.pop_back();
    v.push_back(x);
  }
  return v;
}

const int maxn = 1005;
int N;
int A[maxn];
string S;
string ans;
bool done = false;
void dfs(deque<int> v, int i) {
  if (done) return;
  if (i == N) {
    if (sz(v) == 1) {
      ans = S;
      done = true;
      return;
    }
  }
  else {
    S += 'l';
    dfs(mergeLeft(v, A[i]), i+1);
    S.pop_back();

    S += 'r';
    dfs(mergeRight(v, A[i]), i+1);
    S.pop_back();
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;

  auto lg = [&](int x) {
    int r = -1;
    while (x) {
      r++;
      x >>= 1;
    }
    return r;
  };
  while (T--) {
    cin >> N; 
    F0R(i, N) {
      cin >> A[i];
      A[i] = lg(A[i]);
    }
    deque<int> v;
    done = false;
    ans.clear();
    dfs(v, 0);
    cout << (done ? ans : "no") << '\n';
  }
}
