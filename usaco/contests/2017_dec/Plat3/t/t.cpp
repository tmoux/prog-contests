#include <cstdio>
#include <cassert>
#include <ctime>
#include <iostream>
#include <iomanip>
 
#define NMAX 2000005
 
int c[NMAX];
 
int num[NMAX+1];
 
bool all_recv(int k, int n) {
  for (int i = 1; i <= n; i++) {
    num[i] = 0;
  }
  for (int i = 0; i < k-1; i++) {
    num[c[i]]++;
  }
  int total = 0;
  for (int i = 1; i <= n; i++) {
    total += num[i];
    if (total >= i) {
      return false;
    }
  }
  return true;
}
 
int main() {
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++) {
    int d;
    scanf("%d", &d);
    assert(0 <= d && d < n);
    c[i] = n - d;
  }

  // lo <= the answer < hi
  int lo = 1;
  int hi = n+1;
  while (hi > lo + 1) {
    int mid = (lo + hi) / 2;
    if (all_recv(mid, n)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
 
  int ans = lo;
  printf("%d\n", n - ans);
}
