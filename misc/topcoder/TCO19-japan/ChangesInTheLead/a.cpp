#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 255;
const int M = 1e9+7;
int dp[maxn][maxn][maxn][2];

void madd(int& a, int b) {
    a = (a+b) % M;
}

class ChangesInTheLead
{
    public:
    int count(int H, int A, int C) {
        if (H == 0 && A == 0 && C == 0) return 1;
        dp[1][0][0][0] = 1;
        dp[0][1][0][1] = 1;
        for (int h = 0; h <= H; h++) {
            for (int a = 0; a <= A; a++) {
                for (int c = 0; c <= C; c++) {
                    /*
                    printf("[%d][%d][%d][%d]: %d\n",h,a,c,0,dp[h][a][c][0]);
                    printf("[%d][%d][%d][%d]: %d\n",h,a,c,1,dp[h][a][c][1]);
                    */

                    if (h > a) {
                        madd(dp[h+1][a][c][0],dp[h][a][c][0]);
                        madd(dp[h][a+1][c][0],dp[h][a][c][0]);
                    }
                    else if (a > h) {
                        madd(dp[h][a+1][c][1],dp[h][a][c][1]);
                        madd(dp[h+1][a][c][1],dp[h][a][c][1]);
                    }
                    else { //a == h
                        madd(dp[h+1][a][c][0],dp[h][a][c][0]);
                        madd(dp[h+1][a][c+1][0],dp[h][a][c][1]);

                        madd(dp[h][a+1][c][1],dp[h][a][c][1]);
                        madd(dp[h][a+1][c+1][1],dp[h][a][c][0]);
                    }
                }
            }
        }
        int ans = (dp[H][A][C][0]+dp[H][A][C][1]) % M;
        return ans;
    }
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ChangesInTheLead test;
    cout << test.count(0,0,0) << '\n';
}

