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

#define rep(i, from, to) for (int i = from; i < (to); ++i)
using vi = vector<int>;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<bool>> G(N, vector<bool>(M));
  F0R(i, N) {
    string s; cin >> s;
    for (int j = 0; j < M; j++) {
      G[i][j] = s[j] - '0';
    }
  }
  const int maxn = 505;
  vector<bitset<maxn>> bs(M);
  F0R(j, M) {
    F0R(i, N) {
      if (G[i][j]) bs[j][i] = 1;
    }
  }
  vector<vector<int>> adj(M);

  vector<bool> ignore(M, false);
  vector<int> sameAs(M);
  int numIgnore = 0;
  // If two documents are at same level, merge them
  F0R(i, M) if (!ignore[i]) {
    for (int j = i+1; j < M; j++) {
      if (bs[i] == bs[j]) {
        ignore[j] = true;
        sameAs[j] = i;
        numIgnore++;
      }
    }
  }

  F0R(i, M) {
    if (ignore[i]) continue;
    F0R(j, M) {
      if (ignore[j]) continue;
      if (i != j) {
        if (bs[i] == bs[j]) {
          continue;
        }
        else if (bs[i] == (bs[i] & bs[j])) {
          // cout << i << " <= " << j << endl;
          adj[i].push_back(j);
        }
      }
    }
  }

  vector<int> btoa(M, -1);
  hopcroftKarp(adj, btoa);

  vector<int> next(M, -1);
  vector<int> cnt(M, 0);
  int chains = M - numIgnore;
  F0R(i, M) {
    if (btoa[i] != -1) {
      int j = btoa[i];
      next[j] = i;
      cnt[i]++;
      chains--;
    }
  }

  vector<int> accessGroup(M);
  vector<int> accessLevel(M);
  int curGroup = 1;
  vector<vector<int>> devLevel(N, vector<int>(chains + 1, 1));
  F0R(i, M) if (!ignore[i] && cnt[i] == 0) {
    int j = i;
    int level = 100000;
    bitset<maxn> cur;
    while (j != -1) {
      F0R(k, N) {
        if (!cur[k] && bs[j][k]) {
          devLevel[k][curGroup] = level;
        }
      }
      accessGroup[j] = curGroup;
      accessLevel[j] = level;

      cur = bs[j];
      j = next[j];
      level--;
    }
    curGroup++;
  }

  cout << chains << '\n';
  F0R(i, M) {
    cout << (!ignore[i] ? accessGroup[i] : accessGroup[sameAs[i]]) << ' ';
  }
  cout << '\n';
  F0R(i, M) {
    cout << (!ignore[i] ? accessLevel[i] : accessLevel[sameAs[i]]) << ' ';
  }
  cout << '\n';
  F0R(i, N) {
    for (int j = 1; j <= chains; j++) {
      cout << devLevel[i][j] << ' ';
    }
    cout << '\n';
  }
}
