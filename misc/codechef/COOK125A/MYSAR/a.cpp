#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll a[maxn];

ll ask(int l1, int r1, int l2, int r2) {
  printf("Q %d %d %d %d\n",l1,r1,l2,r2);
  fflush(stdout);
  int x; cin >> x;
  return x;
}

ll q[maxn];
ll diff[maxn];

bool poss() {
  for (int i = 3; i <= n; i++) {
    int nn;
    if (q[i-1] == a[i-1]+diff[i-1]-min(a[1],a[2])) {
      nn = a[i-1]+diff[i-1];
    }
    else {
      if (a[i-1]-min(a[1],a[2]) != q[i-1]) return false;
      nn = a[i-1]-diff[i-1];
    }
    //cout << i << ": " << nn << '\n';
    if (i == n) return nn = a[n];
    a[i] = nn;
  }
  assert(false); return false;
}

int main() {
  cin >> n;
  cin >> a[1] >> a[n];
  diff[1] = ask(1,2,1,2);
  for (int i = 2; i < n; i++) {
    diff[i] = ask(i,i+1,i,i+1);
    q[i] = ask(i,i+1,1,2);
  }
  a[2] = a[1] - diff[1];
  if (poss()) {
    cout << "! ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " \n"[i==n];
    }
    cout << endl;
  }
  else {
    a[2] = a[1] + diff[1];
    assert(poss());
    cout << "! ";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " \n"[i==n];
    }
    fflush(stdout);
  }
}
