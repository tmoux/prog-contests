#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const int NANA = -2e9-9;
int N;
string A, B;
int a[maxn], b[maxn];
int dp[maxn][maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

int f(int i, int j) {
    if (i == N || j == N) return 0;
    if (dp[i][j] >= 0) return dp[i][j];
    dp[i][j] = 0;
    if ((A[i] == 'W' && B[j] == 'L' && a[i] > b[j]) ||
        (A[i] == 'L' && B[j] == 'W' && b[j] > a[i])) {
        amax(dp[i][j],f(i+1,j+1) + a[i] + b[j]);
    }
    amax(dp[i][j],f(i+1,j));
    amax(dp[i][j],f(i,j+1));
    //printf("[%d][%d]: %d\n",i,j,dp[i][j]);
    return dp[i][j];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    cin >> A;
    for (int i = 0; i < N; i++) cin >> a[i];
    cin >> B;
    for (int i = 0; i < N; i++) cin >> b[i];
    memset(dp,-1,sizeof dp);
    int ans = f(0,0);
    cout << ans << '\n';

    return 0;
}

