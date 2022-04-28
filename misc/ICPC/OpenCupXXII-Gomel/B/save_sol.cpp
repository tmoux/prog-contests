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

struct DSU {
  int n;
  vector<int> par;
  vector<int> leftRepr;
  DSU() {}  // need empty constructor for map
  DSU(int _n) {
    n = _n;
    par.resize(n + 1, -1);
    leftRepr.resize(n + 1);
    iota(all(leftRepr), 0);
  }

  int Find(int i) { return par[i] < 0 ? i : par[i] = Find(par[i]); }

  bool Union(int x, int y) {  // return true if x and y were not connected
    // x is on the left, y is on the right
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    int l = leftRepr[x];
    if (par[x] > par[y]) {
      swap(x, y);
      l = leftRepr[y];
    }
    par[x] += par[y];
    par[y] = x;
    leftRepr[x] = l;
    return true;
  }

  int getLeftRepr(int x) { return leftRepr[Find(x)]; }
};

const int maxn = 505, maxm = 5;
int N, M;
int a[maxn][maxm];
int ans[maxn][maxn];
ll tohash[1 << maxm][maxn];

int leftEdge[1 << maxm][maxn], rightEdge[1 << maxm][maxn];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M;
  F0R(i, N) F0R(j, N) ans[i][j] = 2e9;
  F0R(i, N) F0R(j, M) cin >> a[i][j];

  auto get_hash = [&](const vector<int> &v) -> ll {
    ll ans = 0;
    ll mult = 1;
    F0R(i, sz(v)) {
      ans += mult * v[i];
      mult *= N + 1;
    }
    return ans;
  };

  map<ll, set<int>> hashes;
  F0R(i, N) {
    F0R(mask, 1 << M) {
      vector<int> v;
      F0R(k, M) {
        if (mask & (1 << k))
          v.push_back(a[i][k]);
        else
          v.push_back(0);
      }
      ll h = get_hash(v);
      tohash[mask][i] = h;
      hashes[h].insert(i);
    }
  }
  F0R(i, N) {
    F0R(mask, 1 << M) {
      ll h = tohash[mask][i];
      auto it = hashes[h].lower_bound(i);
      if (it == hashes[h].begin())
        leftEdge[mask][i] = *prev(hashes[h].end());
      else
        leftEdge[mask][i] = *prev(it);

      it = hashes[h].upper_bound(i);
      if (it == hashes[h].end())
        rightEdge[mask][i] = *hashes[h].begin();
      else
        rightEdge[mask][i] = *it;
    }
  }

  vector<ll> hs;
  for (auto &[h, _] : hashes) hs.push_back(h);

  F0R(i, N) {
    cout << i << endl;
    map<ll, DSU> dsus;
    cout << sz(hs) << endl;
    // for (auto h : hs) { dsus[h] = DSU(N); }
    continue;
    queue<array<int, 2>> q;
    vector<vector<int>> dist(1 << M, vector<int>(N, 2e9));
    F0R(mask, 1 << M) {
      dist[mask][i] = 0;
      q.push({mask, i});
    }

    auto upd = [&](int mask, int j, int curd) -> void {
      if (ckmin(dist[mask][j], curd + 1)) q.push({mask, j});
    };

    auto should_stop = [&](int curj, int oldj, int stop) -> bool {
      if (stop < oldj) {
        return curj <= stop || curj >= oldj;
      } else {
        return oldj <= curj && curj <= stop;
      }
    };

    while (!q.empty()) {
      auto [mask, j] = q.front();
      q.pop();
      int d = dist[mask][j];
      int nj;

      F0R(k, M) {
        if (mask & (1 << k)) {
          ll h = tohash[mask ^ (1 << k)][j];
          int stop = leftEdge[mask][j];
          int nj = dsus[h].getLeftRepr(j);
          if (nj == j) nj = dsus[h].getLeftRepr(leftEdge[mask ^ (1 << k)][nj]);
          while (true) {
            /*
            if (j == 5 && mask == 4) {
              cout << "curd: " << d << endl;
              DEBUG(j);
              DEBUG(stop);
              DEBUG(nj);
              DEBUG(h);
              cout << dsus[h].Find(nj) << ' ' << dsus[h].Find(stop) << endl;
              cout << "should_stop: " << should_stop(nj, j, stop) << endl;
            }
            */
            if (should_stop(nj, j, stop)) break;
            upd(mask ^ (1 << k), nj, d);
            dsus[h].Union(leftEdge[mask ^ (1 << k)][nj], nj);
            if (nj == dsus[h].getLeftRepr(nj))
              break;
            else
              nj = dsus[h].getLeftRepr(nj);
          }
        }
      }

      nj = leftEdge[mask][j];
      upd(mask, nj, d);

      nj = rightEdge[mask][j];
      upd(mask, nj, d);

      F0R(k, M) {
        if (!(mask & (1 << k))) { upd(mask ^ (1 << k), j, d); }
      }
      F0R(k, M) {
        if ((mask & (1 << k))) { upd(mask ^ (1 << k), j, d); }
      }
    }
    /*
    F0R(j, N) {
      F0R(mask, 1 << M) {
        cout << j << ' ' << mask << ": " << dist[mask][j] << endl;
      }
    }
    */
    // update ans
    F0R(j, N) ans[j][i] = dist[0][j];
  }
  return 0;
  F0R(i, N) F0R(j, N) { cout << ans[i][j] << " \n"[j == N - 1]; }
}

