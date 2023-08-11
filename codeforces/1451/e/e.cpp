#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 16;
int x[1<<maxn], ans[1<<maxn];
int mask[1<<maxn];

enum Query { AND, OR, XOR };
int ask(int i, int j, Query q) {
  switch (q) {
    case AND : cout << "AND"; break;
    case OR  : cout << "OR"; break;
    case XOR : cout << "XOR"; break;
  }
  cout << ' ' << i+1 << ' ' << j+1 << endl;
  int x; cin >> x;
  assert(x != -1);
  return x;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int len; cin >> len;
  int n = 0;
  for (int i = 1; i < len; i <<= 1) ++n;

  for (int i = 1; i < len; i++) {
    x[i] = ask(0,i,XOR);
  }
  memset(mask,-1,sizeof mask);
  int a = -1, b = -1;
  for (int i = 1; i < len; i++) {
    if (x[i] == 0) {
      a = i;
      b = 0;
      break;
    }
    for (int s = x[i]; ;s=((s-1)&x[i])) {
      if (mask[s] != -1) {
        a = mask[s];
        b = i;
        break;
      }
      if (s == 0) break;
    }
    mask[x[i]] = i;
    if (a != -1 && b != -1) break;
  }
  assert(a != -1 && b != -1);
  //cout << "a = " << a << ", b = " << b << endl;
  int andA = ask(0,a,AND);
  int andAB = ask(a,b,AND);
  for (int j = 0; j < n; j++) {
    if (!(x[a]&(1<<j))) {
      ans[0] |= andA & (1<<j);
    }
    else {
      ans[0] |= (andAB ^ (1<<j)) & (1<<j);
    }
  }
  for (int i = 1; i < len; i++) {
    ans[i] = ans[0] ^ x[i];
  }
  //output
  cout << "! ";
  for (int i = 0; i < len; i++) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
