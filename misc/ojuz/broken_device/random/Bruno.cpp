#include "Brunolib.h"
#include <bits/stdc++.h>
using namespace std;

long long Bruno( int N, int A[] ){
  std::mt19937 rng(6969);
  const int MX = 60;
  int B[MX][N];
  for (int i = 0; i < MX; i++) {
    for (int j = 0; j < N; j++) {
      B[i][j] = rng() & 1;
    }
  }

  long long ans = 0;
  for (int j = 0; j < N; j++) if (A[j]) {
    for (int i = 0; i < MX; i++) {
      if (B[i][j]) ans ^= 1LL << i;
    }
  }

  return ans;
}
