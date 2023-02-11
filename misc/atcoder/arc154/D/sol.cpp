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

bool ask(int i, int j, int k) {
  printf("? %d %d %d\n", i+1, j+1, k+1); fflush(stdout);
  string s; cin >> s;
  return s == "Yes";
}

void answer(vector<int> v) {
  cout << "! ";
  for (auto x: v) cout << x << ' ';
  cout << endl;
}

int main() {
  int N; cin >> N;
  int idx = 0;
  FOR(i, 1, N) {
    if (ask(idx, idx, i)) {
      idx = i;
    }
  }

  auto lt = [&](int i, int j) {
    return ask(j, idx, i);
  };

  auto sort_indices = y_combinator([&](auto sort, vector<int>& v) -> void {
      if (sz(v) == 1) return;
      vector<int> l, r;
      F0R(i, sz(v)/2) l.push_back(v[i]);
      FOR(i, sz(v)/2, sz(v)) r.push_back(v[i]);
      sort(l);
      sort(r);
      v.clear();
      for (int i = 0, j = 0; i < sz(l) || j < sz(r);) {
        if (j == sz(r)) v.push_back(l[i++]);
        else if (i == sz(l)) v.push_back(r[j++]);
        else if (lt(l[i], r[j])) v.push_back(l[i++]);
        else v.push_back(r[j++]);
      }
  });

  vector<int> v(N); iota(all(v), 0);
  sort_indices(v);

  vector<int> perm(N);
  F0R(i, N) {
    perm[v[i]] = i+1;
  }
  answer(perm);
}
