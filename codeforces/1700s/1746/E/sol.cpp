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

bool ask(const vector<int>& v) {
  cout << "?";
  cout << ' ' << sz(v);
  for (auto x: v) {
    cout << ' ' << x;
  }
  cout << endl;
  string s; cin >> s;
  return s == "YES";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  set<int> S;
  for (int i = 1; i <= N; i++) {
    S.insert(i); 
  }

  auto remove = [&](const vector<int>& v) {
    for (auto x: v) S.erase(x);
  };

  while (sz(S) >= 3) {
    vector<int> A[3];
    int i = 0;
    for (int x: S) {
      A[i % 3].push_back(x);
      i++;
    }

    if (ask(A[0])) {
      if (ask(A[1])) {
        remove(A[2]);
      }
      else {
        remove(A[1]);
      }
    }
    else if (ask(A[0])) {
      if (ask(A[1])) {
        remove(A[2]);
      }
      else {
        remove(A[1]);
      }
    }
    else remove(A[0]);
  }

  assert(!S.empty());
  for (auto x: S) {
    cout << "! " << x << endl;
    string s; cin >> s;
    if (s == ":)") return 0;
  }
}
