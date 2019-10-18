#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 1e9+7;
int N, T, Q;
int t[maxn];

const int BLK = 50;
int bucket[maxn], start[maxn/BLK+5], endd[maxn/BLK+5];

int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> T >> Q;
    for (int i = 1; i <= N; i++) 
        cin >> t[i];
    for (int i = 1; i <= N; i++) {
        bucket[i] = (i-1)/BLK;
        if (i == 1 || bucket[i] != bucket[i-1]) 
            start[bucket[i]] = i;
        if (i == N || bucket[i] != i/BLK)
            endd[bucket[i]] = i;
    }
    for (int b = 0; b <= bucket[N]; b++) {
        for (int i = start[b]; i <= endd[b]; i++) {
            if (i == start[b]) {
                dp[i][0] = 1;
                dp[i][t[i]] = 1;
            }
            else {
                for (int j = 0; j <= T; j++) {
                    dp[i][j] = dp[i-1][j];
                    if (j-t[i] >= 0) 
                        madd(dp[i][j],dp[i-1][j-t[i]]);
                }
            }
        }
    }
}

