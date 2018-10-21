/*
ID: silxikys
PROG: cowxor
LANG: C++
*/

#include <cstdio>

#define MXN 101000

using namespace std;

int xr[MXN], prev[MXN][2], best[MXN];
int a, wyk, res, n, x;
int tmp[2];
bool fnd;

int main() {
    freopen("cowxor.in", "r", stdin);
    freopen("cowxor.out", "w", stdout);
    scanf("%i", &n);
    xr[0] = 0;
    for (a = 0; a < n; a++ ) {
        scanf("%d", &x);
        xr[a+1] = xr[a] ^ x;
    }
    for (a = 0; a <= n; a++ ) {
        prev[a][0] = a-1;
        prev[a][1] = -1;
        best[a] = a-1;
    }
    wyk = 22;
    res = 0;
    while (wyk--) {
        for (a = 1; a <= n; a++ )
            if (prev[a][0] == -1)
                prev[a][1] = -1;
            else {
                if (xr[a] >> wyk != xr[prev[a][0]] >> wyk) {
                    tmp[0] = prev[prev[a][0]][1];
                    tmp[1] = prev[a][0];
                } else {
                    tmp[0] = prev[a][0];
                    tmp[1] = prev[prev[a][0]][1];
                }
                prev[a][0] = tmp[0];
                prev[a][1] = tmp[1];
            }
        fnd = false;
        for (a = 1; a <= n; a++ )
            if (0 <= best[a])
                if ((xr[a] >> wyk) % 2 != (xr[best[a]] >> wyk) % 2 ||
                                      0 <= prev[best[a]][1])
                    fnd = true;
        if (fnd) {
            res |= 1 << wyk;
            for (a = 1; a <= n; a++ )
                if (0 <= best[a] &&
                              (xr[a] >> wyk) % 2 == (xr[best[a]] >> wyk) % 2)
                    best[a] = prev[best[a]][1];
        }
    }
    for (a = 0; best[a] == -1; a++ );
    printf("%d %d %d\n", res, best[a]+1, a);
    return 0;
}