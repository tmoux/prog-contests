#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

int n, m, k;

vector<vector<bool>> grid;
vector<vector<int>> square;

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m;
}

bool check(int d) {
  //check if places >= d are connected
  int cnt = 0;
  vector<pair<int,int>> v;
  F0R(i, n) {
    F0R(j, m) {
      if (square[i][j] >= d) {
        cnt++;
        v.push_back({i,j});
      }
    }
  }
  if (cnt == 0) return false;
  queue<pair<int,int>> q; q.push(v[0]);
  vector<vector<bool>> vis(n, vector<bool>(m, false));
  int numSeen = 0;
  while (!q.empty()) {
    auto f = q.front(); q.pop();
    int x = f.first;
    int y = f.second;
    if (!vis[x][y]) {
      numSeen++;
      vis[x][y] = true;
      F0R(k, 4) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (!valid(nx,ny)) continue;
        if (square[nx][ny] >= d) q.push({nx,ny});
      }
    }
  }
  if (numSeen < cnt) return false;
  
  vector<int> row(m,0);
  F0R(i, n) {
    F0R(j, m) row[j]--;
    int rt = 0;
    F0R(j, m) {
      //decrement row value by 1
      if (square[i][j] >= d) {
        ckmax(rt,j);
        while (rt < j+d) {
          row[rt++] = d;
        }
      }
    }

    F0R(j, m) {
      if (!grid[i][j] && row[j] <= 0) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m >> k;
  grid = vector<vector<bool>>(n, vector<bool>(m, false));
  square = vector<vector<int>>(n, vector<int>(m));
  F0R(i, k) {
    int x, y; cin >> x >> y;
    x--; y--;
    grid[x][y] = true;
  }

  F0Rd(i, n) {
    F0Rd(j, m) {
      if (!grid[i][j]) {
        square[i][j] = n+m;
        ckmin(square[i][j], i+1<n?square[i+1][j]:0);
        ckmin(square[i][j], j+1<m?square[i][j+1]:0);
        ckmin(square[i][j], (i+1<n && j+1<m)?square[i+1][j+1]:0);
        square[i][j]++;
      }
    }
  }

  /*
  F0R(i, n) {
    F0R(j, m) {
      cout << square[i][j] << ' ';
    }
    cout << '\n';
  }
  */

  int lo = 0, hi = min(n,m) + 1;
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    if (check(mid)) {
      lo = mid;
    }
    else hi = mid;
  }
  cout << (lo == 0 ? -1 : lo) << '\n';
}
