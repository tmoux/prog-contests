#include <bits/stdc++.h>
using namespace std;

struct Sparse
{
  //sparse table data structure for gcd
  static const int mk = 18; //change this number based on bounds
  int* tb[mk];
  static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
  Sparse(int *a, int n) {
    for (int i = 0; i < mk; i++) {
      tb[i] = new int[n];
    }
    for (int i = 0; i < n; i++) tb[0][i] = a[i];
    for (int k = 1; k <= lg(n); k++) {
      for (int i = 0; i < n; i++) {
        int nx = i + (1<<(k-1));
        if (nx < n) tb[k][i] = __gcd(tb[k-1][i],tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  int gcd(int l, int r) {
    int g = lg(r-l+1);
    return __gcd(tb[g][l],tb[g][r-(1<<g)+1]);
  }
};

const int maxn = 2e5+5;
int n;
int a[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<array<int, 2>> intervals;
  Sparse sparse(a, n);
  for (int i = 0; i < n; i++) {
    int j = i;
    for (int k = 17; k >= 0; k--) {
      int nj = j + (1<<k);
      if (nj < n && sparse.gcd(i, nj) >= nj-i+1) j = nj;
    }
    if (sparse.gcd(i, j) == j-i+1) {
      intervals.push_back({i,j});
    }
  }
  reverse(intervals.begin(), intervals.end());

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (!intervals.empty() && intervals.back()[1] == i) {
      intervals.pop_back();
      ans++;
      while (!intervals.empty() && intervals.back()[0] <= i) {
        assert(i <= intervals.back()[1]);
        intervals.pop_back();
      }
    }
    cout << ans << ' ';
  }
  cout << '\n';
}
