#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2002; // 0 -> 2001
bool valid[maxn];

int mn[maxn], mx[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    for (int x2 = 0; x2 < maxn; x2++) {
      if (valid[x2]) {

        int xx = x2 - 1000;
        ans = max(ans, (x - xx) * (x - xx) + (y - mn[x2]) * (y - mn[x2]));
        ans = max(ans, (x - xx) * (x - xx) + (y - mx[x2]) * (y - mx[x2]));
      }
    }

    if (!valid[x+1000]) {
      valid[x+1000] = true;
      mn[x+1000] = y;
      mx[x+1000] = y;
    }
    else {
      mn[x+1000] = min(mn[x+1000], y);
      mx[x+1000] = max(mx[x+1000], y);
    }
  }

  long double ret = sqrt(ans);
  cout << fixed << setprecision(10) << ret << '\n';
}


