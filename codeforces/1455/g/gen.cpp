#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  int S = 30002;
  printf("%d %d\n",n+n/2,S);
  for (int i = 0; i < n/2; i++) {
    printf("set %d %d\n",i+1,1);
    printf("if %d\n",i+1);
  }
  for (int i = 0; i < n/2; i++) {
    printf("end\n");
  }
}

