#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
const int b = 70000;
int N, K;

int dp[2][2*b];

void madd(int& a, int b) {
    a = (a+b) % M;
}
void msub(int& a, int b) {
    a = (a-b+M) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int cnt[b];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    int sq = (int)(sqrt(N));
    map<int,int> mp;
    for (int i = 1; i <= sq; i++) {
        dp[0][i] = 1 + dp[0][i-1];
        cnt[i] = 1;
        //cout << i << ": " << dp[0][i] << '\n';
    }
    int mx = sq;
    int pt = sq+1;
    for (int i = N/(sq+1); i >= 1; i--) {
        cnt[pt] = (N/i) - (N/(i+1));
        dp[0][pt] = cnt[pt] + dp[0][pt-1];
        mp[i] = pt;
        mx = pt;
        //cout << i << ": " << dp[0][pt] << '\n';
        pt++;
    }
    for (int q = 1; q < K; q++) {
        int curr = q&1;
        int other = curr^1;
        for (int i = 1; i <= sq; i++) {
            int r = mp.count(i) ? mp[i] : N/i;
            dp[curr][i] = dp[other][r];
        }
        pt = sq + 1;
        for (int i = N/(sq+1); i >= 1; i--) {
            int r = i;
            dp[curr][pt] = mult(cnt[pt],dp[other][r]);
            pt++;
        }
        /*
        for (int i = 1; i <= mx; i++) {
            cout << i << ": " << dp[curr][i] << '\n';
        }
        */
        for (int i = 1; i <= mx; i++) {
            madd(dp[curr][i],dp[curr][i-1]);
        }
    }
    int ans = dp[(K-1)&1][mx];
    cout << ans << '\n';
}

