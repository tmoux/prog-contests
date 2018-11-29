/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */
#include <bits/stdc++.h>
using namespace std;

int get(int A, int C, int r, int g, int b) {
	return A*(r*r+g*g+b*b)+C*min(r,min(g,b));
}

int main() {
  //  uncomment the following lines if you want to read/write from files
  //  freopen("input.txt", "r", stdin);
  //  freopen("output.txt", "w", stdout);
  int testcase, T;
  int A, C, r, g, b;

  assert(1 == scanf("%d", &T));
  for (testcase = 0; testcase < T; testcase++) {
    assert(5 == scanf("%d %d %d %d %d", &A, &C, &r, &g, &b));
  	int rr = get(A,C,r+1,g,b);
  	int gg = get(A,C,r,g+1,b);
  	int bb = get(A,C,r,g,b+1);
  	if (rr > max(gg,bb)) {
  		printf("RED\n");
  	}
  	else if (gg > bb) {
  		printf("BLUE\n");
  	}
  	else {
  		printf("GREEN\n");
  	}
  }
  return 0;
}
