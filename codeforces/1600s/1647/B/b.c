#include <stdio.h>

int main() {
  int T; scanf("%d\n", &T);
  while (T--) {
    int n, m;
    scanf("%d %d\n", &n, &m);
    char a[100][100];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%c", &a[i][j]);
        a[i][j] -= '0';
      }
      scanf("\n");
    }

    int ans = 1;
    for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < m-1; j++) {
        int cnt = a[i][j] + a[i][j+1] + a[i+1][j] + a[i+1][j+1];
        if (cnt == 3) ans = 0;
      }
    }
    printf("%s\n", ans?"YES":"NO");
  }
}
