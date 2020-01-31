#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    freopen("java2016.in","r",stdin); freopen("java2016.out","w",stdout);
    int c; cin >> c;
    if (c == 0) {
        printf("?/?/?\n");
        return 0;
    }
    printf("a = ? max ?\n");
    printf("b = a max a\n");
    printf("c = b max b\n");
    printf("d = c max c\n");
    printf("e = d max d\n");
    printf("f = e max e\n");
    printf("g = f max f\n");
    printf("h = g max g\n");
    printf("i = h max h\n");
    printf("j = i max i\n");
    printf("k = j max j\n");
    printf("l = k max k\n");
    printf("m = (l) / (l)\n");
    int sq = sqrt(c);
    int div = c/sq;
    int rem = c % sq;
    printf("n = m");
    for (int i = 0; i < sq-1; i++) {
        printf("+m");
    }
    printf("\n");
    printf("n");
    for (int i = 0; i < div-1; i++) {
        printf("+n");
    }
    for (int i = 0; i < rem; i++) {
        printf("+m");
    }
    printf("\n");

    //printf("sq = %d, div = %d, rem = %d\n",sq,div,rem);
}

