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

const int maxn = 3e5+5;
int N, K;

int Div[maxn];
int spf[maxn];

vector<int> v;
int cur;
void rec(int i) {
  if (cur == K) {
    cout << "Yes\n";
    vector<int> C(N+1);
    for (auto x: v) C[x] = 1;
    vector<int> ans;
    FOR(j, 1, N+1) if (!C[j]) ans.push_back(j);
    cout << sz(ans) << '\n';
    for (auto x: ans) cout << x << ' ';
    cout << endl;
    exit(0);
  }

  if (i >= 1) {
    int c = Div[i] - Div[i-1] + (N / i - 1);
    for (int j: v) if (j % i == 0) c--;
    if (cur - c >= K) {
      cur -= c;
      v.push_back(i);
      rec(i-1);
      v.pop_back();
      cur += c;
    }
    rec(i-1);
  }
}


void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> N >> K;
  for (int i = 1; i <= N; i++) {
    for (int j = i+i; j <= N; j += i) {
      Div[j]++;
    }
  }
  for (int i = 1; i <= N; i++) {
    Div[i] += Div[i-1];
  }

  if (K > Div[N]) {
    cout << "No\n";
  }
  else {
    while (N-1 >= 1 && Div[N-1] >= K) N--;
    cur = Div[N];
    rec(N);
  }
}
