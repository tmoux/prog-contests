#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld,ld> pd;
typedef vector<int> vi;
typedef vector<ll> vl;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define trav(a, x) for (auto &a : x)

#define sz(x) (int) (x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

vector<vi> g, gr;
vector<bool> used;
vi ord, comp;

vi compOf;
int nc = 0;

void dfs1(int v) {
  used[v] = true;
  trav(a, g[v]) {
    if (!used[a]) dfs1(a);
  }
  ord.pb(v);
}

void dfs2(int v) {
  used[v] = true;
  comp.pb(v);
  trav(a, gr[v]) {
    if (!used[a]) dfs2(a);
  }
}

void findSCCs(int n) {
  ord.clear();
  used.assign(n, false);
  F0R(i, n) {
    if (!used[i]) dfs1(i);
  }
  used.assign(n, false);
  F0R(i, n) {
    int v = ord[n-1-i];
    if (!used[v]) {
      dfs2(v);
      trav(a, comp) {
        compOf[a] = nc;
      }
      nc++;
      comp.clear();
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T; cin >> T;
  while (T--) {
    nc = 0;
    int N, M; cin >> N >> M;
    compOf = vi(N);
    g = vector<vi>(N);
    gr = vector<vi>(N);
    F0R(i, M) {
      int X, Y; cin >> X >> Y;  X--; Y--;
      g[X].pb(Y); gr[Y].pb(X);
    }
    findSCCs(N);
    if (nc == 1) {
      cout << 0 << nl;
      continue;
    }
    int ind[nc], od[nc];
    F0R(i, nc) {
      ind[i] = 0, od[i] = 0;
    }
    F0R(i, N) {
      trav(a, g[i]) {
        if (compOf[a] == compOf[i]) continue;
        ind[compOf[a]]++;
        od[compOf[i]]++;
      }
    }
    int a1 = 0, a2 = 0;
    F0R(i, nc) {
      if (ind[i] == 0) a1++;
      if (od[i] == 0) a2++;
    }
    cout << max(a1, a2) << nl;
  }

  return 0;
}
