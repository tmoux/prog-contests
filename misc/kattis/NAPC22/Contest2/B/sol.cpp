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

const int maxn = 10005;
int N;
vector<int> adj[maxn];

int colors[maxn][2];
int id = 1;
void dfs(int i, int p, int c, bool onlychild) {
  if (p == -1) {
    colors[i][0] = id++;
    colors[i][1] = id++;

    if (adj[i].size() > 1) {
      int cnt = 0;
      for (int j: adj[i]) if (j != p) {
        if (cnt % 2 == 0) {
          dfs(j, i, colors[i][0], false);
        }
        else {
          dfs(j, i, colors[i][1], false);
        }
        cnt++;
      }
    }
    else {
      int j = adj[i][0];
      dfs(j, i, colors[i][0], true);
    }
  }
  else {
    if (onlychild) {
      colors[i][0] = colors[p][0];
      colors[i][1] = colors[p][1];
    }
    else {
      colors[i][0] = c;
      colors[i][1] = id++;
    }

    for (int j: adj[i]) if (j != p) {
      dfs(j, i, colors[i][1], false);
    }
  }

}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  REP(N-1) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, -1, -1, false);
  for (int i = 1; i <= N; i++) {
    cout << colors[i][0] << ' ' << colors[i][1] << '\n';
  }
}

