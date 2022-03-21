#include <stdio.h>

int main() {
  char buf[100];
  int ans = 0;
  while (scanf("%s", buf) != EOF) ans++;
  printf("%d\n", ans);
}
