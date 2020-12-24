#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double PI = atan(1)*4;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << fixed << setprecision(10);
  int M, N;
  double R;
  cin >> M >> N >> R;
  int ax, ay, bx, by; cin >> ax >> ay >> bx >> by;
  double ans = 1e18;
  for (int r = 0; r <= min(ay,by); r++) {
    double tot = PI*(r/(double)N)*(abs(ax-bx)/(double)M);
    tot += (ay-r)/(double)N;
    tot += (by-r)/(double)N;
    tot *= R;
    ans = min(ans,tot);
    //cout << r << ": " << tot << endl;
  }
  cout << ans << '\n';
}

