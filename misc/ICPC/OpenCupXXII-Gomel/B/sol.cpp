#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define F0R(i, a) for (int i = 0; i < (a); i++)
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}

struct DSU {
  int n;
  vector<int> par;
  vector<int> leftRepr;
  DSU() {}  // need empty constructor for map
  DSU(int _n) {
    n = _n;
    par.resize(n, -1);
    leftRepr.resize(n);
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
vector<vector<int>> leftEdgeC;
vector<vector<int>> compress, uncompress;
vector<int> hash_size;

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
  vector<ll> hs;
  for (auto &[h, _] : hashes) hs.push_back(h);
  sort(all(hs));
  map<ll, int> compressHashes;
  F0R(i, sz(hs)) { compressHashes[hs[i]] = i; }
  int H = sz(hs);
  compress.resize(H);
  uncompress.resize(H);
  hash_size.resize(H);
  leftEdgeC.resize(H);
  F0R(i, H) leftEdgeC[i].resize(hash_size[i]);

  for (auto &[h, s] : hashes) {
    int id = compressHashes[h];
    compress[id].resize(N, -1);
    uncompress[id].resize(sz(s), -1);
    leftEdgeC[id].resize(sz(s));
    int i = 0;
    for (auto x : s) {
      compress[id][x] = i;
      uncompress[id][i] = x;
      i++;
    }
    hash_size[id] = sz(s);
  }

  F0R(i, N) {
    F0R(mask, 1 << M) {
      ll h = tohash[mask][i];
      auto it = hashes[h].lower_bound(i);
      if (it == hashes[h].begin())
        leftEdge[mask][i] = *prev(hashes[h].end());
      else
        leftEdge[mask][i] = *prev(it);

      auto &comp = compress[compressHashes[h]];
      leftEdgeC[compressHashes[h]][comp[i]] = comp[leftEdge[mask][i]];

      it = hashes[h].upper_bound(i);
      if (it == hashes[h].end())
        rightEdge[mask][i] = *hashes[h].begin();
      else
        rightEdge[mask][i] = *it;
    }
  }

  F0R(i, N) {
    F0R(mask, 1 << M) { tohash[mask][i] = compressHashes[tohash[mask][i]]; }
  }

  F0R(i, N) {
    vector<DSU> dsus(H);
    F0R(i, H) { dsus[i] = DSU(hash_size[i]); }
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
          int h = tohash[mask ^ (1 << k)][j];
          auto &dsu = dsus[h];
          auto &comp = compress[h];
          int jj = comp[j];
          int stop = comp[leftEdge[mask][j]];
          int nj = dsu.getLeftRepr(jj);
          if (nj == jj) nj = dsu.getLeftRepr(leftEdgeC[h][nj]);
          while (true) {
            if (should_stop(nj, jj, stop)) break;
            upd(mask ^ (1 << k), uncompress[h][nj], d);
            dsu.Union(leftEdgeC[h][nj], nj);
            if (nj == dsu.getLeftRepr(nj))
              break;
            else
              nj = dsu.getLeftRepr(nj);
          }
        }
      }

      nj = leftEdge[mask][j];
      upd(mask, nj, d);
      nj = rightEdge[mask][j];
      upd(mask, nj, d);
      F0R(k, M) if (!(mask & (1 << k))) upd(mask ^ (1 << k), j, d);
      F0R(k, M) if ((mask & (1 << k))) upd(mask ^ (1 << k), j, d);
    }
    F0R(j, N) ans[j][i] = dist[0][j];
  }
  F0R(i, N) F0R(j, N) cout << ans[i][j] << " \n"[j == N - 1];
}
