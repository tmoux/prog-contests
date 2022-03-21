#include <stdio.h>

#define N 1005
char c[N][N];

int main() {
  int len = 1;
  c[1][0] = '1';
  for (int i = 2; i <= 1000; i++) {
    if (i % 3 == 0) {
      for (int j = 0; j < len; j++) c[i][j] = c[i-1][j];
      c[i][len++] = '1';
    }
    else if (i % 3 == 1) {
      for (int j = 0; j < len; j++) c[i][j] = c[i-1][j] == '1' ? '2' : '1';
      c[i][len++] = '1';
    }
    else {
      for (int j = 0; j < len; j++) c[i][j] = c[i-1][j] == '1' ? '2' : '1';
    }
  }
  int T; scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    printf("%s\n", c[n]);
  }
}
