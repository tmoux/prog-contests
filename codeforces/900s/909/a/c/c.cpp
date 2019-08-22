#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005, M = 1e9+7;
int N;

int suf[maxn][maxn];
int dp[maxn][maxn]; //i'th // depth
//if prev is f: this one has to depth+1
//if prev is s: can 

char a[maxn];

void madd(int& a, int b) {
    a = (a+b) % M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    dp[0][1] = 1;
    suf[0][1] = 1;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < N; i++) {
        for (int d = N; d >= 1; d--) {
            madd(suf[i-1][d],suf[i-1][d+1]);
        }

        for (int d = 1; d <= N; d++) {
            if (a[i-1] == 'f') {
                dp[i][d] = dp[i-1][d-1];
            }
            else {
                dp[i][d] = suf[i-1][d];
            }
            suf[i][d] = dp[i][d];
            //cout << dp[i][d] << ' ';
        }
        //cout << '\n';
    }
    int ans = 0;
    for (int d = 1; d <= N; d++) {
        madd(ans,dp[N-1][d]);
    }
    cout << ans << '\n';
}

