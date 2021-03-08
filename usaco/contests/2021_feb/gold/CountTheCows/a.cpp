#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp1[3][2][2], dp2[3][2][2];

ll exp3[40];

void solve(ll d, ll x, ll y) {
  memset(dp1,0,sizeof dp1);
  dp1[1][0][0] = 1;
  for (int i = 0; i < 39; i++) {
    memset(dp2,0,sizeof dp2);
    int dd = (d/exp3[i])%3;
    int xd = (x/exp3[i])%3;
    int yd = (y/exp3[i])%3;
    for (int cmp: {0,1,2}) {
      for (int xc: {0,1}) {
        for (int yc: {0,1}) {
          for (int j: {0,1,2}) {
            int XD = (xd+xc+j)%3, XC = (xd+xc+j)/3;
            int YD = (yd+yc+j)%3, YC = (yd+yc+j)/3;
            int CMP = cmp;
            if (j > dd) CMP = 2;
            if (j < dd) CMP = 0;
            if (XD%2 == YD%2)
              dp2[CMP][XC][YC] += dp1[cmp][xc][yc];
          }
        }
      }
    }
    swap(dp1,dp2);
  }
  cout << (dp1[0][0][0]+dp1[1][0][0]) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  exp3[0] = 1;
  for (int i = 1; i < 40; i++) exp3[i] = exp3[i-1] * 3;
  int q; cin >> q;
  while (q--) {
    ll d, x, y; cin >> d >> x >> y;
    solve(d,x,y);
  }
}
