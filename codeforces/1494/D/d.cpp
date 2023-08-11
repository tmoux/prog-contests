#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) begin(x),end(x)
template<typename T>
void remove_duplicates(vector<T>& v) {
  sort(all(v));  
  v.erase(unique(all(v)),v.end());
}
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

const int maxn = 1005;
int n;
int a[maxn][maxn];

int ans[maxn];
int par[maxn];

int N;
int rec(vector<int> v) {
  if (v.size() == 1) {
    int x = v[0];
    ans[x] = a[x][x];
    return x;
  }
  int rt = ++N; 
  int mx = 0;
  for (int i: v) for (int j: v) {
    mx = max(mx,a[i][j]);
  }
  for (int i: v) if (!par[i]) {
    vector<int> u;
    for (int j: v) if (a[i][j] < mx) u.push_back(j);
    par[rec(u)] = rt;
  }
  ans[rt] = mx;
  return rt;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  vector<int> v;
  for (int i = 1; i <= n; i++) v.push_back(i);
  N = n;
  int rt = rec(v);
  //output
  cout << N << '\n';
  for (int i = 1; i <= N; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  cout << rt << '\n';
  for (int i = 1; i <= N; i++) if (i != rt) {
    cout << i << ' ' << par[i] << '\n';
  }
}
