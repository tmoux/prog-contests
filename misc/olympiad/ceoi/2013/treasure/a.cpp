#include <bits/stdc++.h>
#include "treasure.h"
using namespace std;
using ll = long long;

const int maxn = 105;
int pre[maxn][maxn];

void findTreasure (int N) {
    for (int i = N; i >= 1; i--) {
        for (int j = N; j >= 1; j--) {
            if (i > N/2 && j > N/2) {
                pre[i][j] = countTreasure(1,1,i,j);
            }
            else if (i > N/2 && j <= N/2) {
                pre[i][j] = pre[i][N] - countTreasure(1,j+1,i,N);
            }
            else if (j > N/2 && i <= N/2) {
                pre[i][j] = pre[N][j] - countTreasure(i+1,1,N,j);
            }
            else {
                pre[i][j] = pre[i][N] + pre[N][j] - pre[N][N] + countTreasure(i+1,j+1,N,N);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (pre[i][j] - pre[i-1][j] - pre[i][j-1] + pre[i-1][j-1] == 1) {
                Report(i,j);
            }
        }
    }
}