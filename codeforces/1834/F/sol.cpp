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

const int maxn = 4e5+5;
int N, P[maxn], Pr[maxn];

int Sum[maxn], Sumr[maxn];

void add(int l, int r, int* A) {
  A[l]++;
  A[r+1]--;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> P[i];
    Pr[N-1-i] = P[i];
  }
  F0R(i, N) {
    int j = i - P[i] + 1;
    if (0 <= j) {
      add(j, i, Sum);
    }
    else {
      add(0, i, Sum);
      add(j+N, N-1, Sum);
    }
  }
  F0R(i, N) {
    int j = i - Pr[i] + 1;
    if (0 <= j) {
      add(j, i, Sumr);
    }
    else {
      add(0, i, Sumr);
      add(j+N, N-1, Sumr);
    }
  }
  FOR(i, 1, N) {
    Sum[i] += Sum[i-1];
    Sumr[i] += Sumr[i-1];
  }
  // F0R(i, N) {
  //   cout << Sum[i] << ' ';
  // }
  // cout << endl;

  int pos = 0, w = 0;

  auto getans = [&]() -> int {
    if (w == 0) return N - Sum[pos];
    else return N - Sumr[pos];
  };
  auto shift = [&](int k) {
    // cout << "shifting by " << k << endl;
    // if (w == 0) {
      pos = (pos + k) % N;
    // }
    // else {
    //   pos = (pos - k + N) % N;
    // }
  };

  cout << getans() << '\n';
  int Q; cin >> Q;
  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int k; cin >> k;
      shift(k);
    }
    else if (t == 2) {
      int k; cin >> k;
      shift(N - k);
    }
    else {
      pos = N - 1 - pos;
      w ^= 1;
      shift(1);
    }
    // cout << "pos " << pos << ' ' << w << endl;
    cout << getans() << '\n';
  }
}
