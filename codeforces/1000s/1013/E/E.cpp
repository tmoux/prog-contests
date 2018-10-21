#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, A[maxn];
int dp[maxn][maxn][2];

int f(int i, int k, bool j) {
    //j is 1 if the curr is bigger than the prev
    if (k <= 0) return 0;
    if (i > n) return 999999999; //means not got target yet
    if (dp[i][k][j] >= 0) return dp[i][k][j];
    if (A[i] > A[i-1] && A[i] > A[i+1]) {
        //is hill
        return dp[i][k][j] = min(f(i+2,k-1,0),f(i+1,k,0));
    }
    else {
        int num = 0;
        if (A[i] <= A[i-1]) num += A[i-1] - A[i] + 1;
        int orig = A[i+1];
        if (A[i] <= A[i+1]) {
            num += A[i+1] - A[i] + 1;
            A[i+1] = A[i] - 1;
        }
        dp[i][k][j] = (num + f(i+2,k-1,1));
        A[i+1] = orig;
        dp[i][k][j] = min(dp[i][k][j],f(i+1,k,0));
        return dp[i][k][j];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    A[0] = -999; A[n+1] = -999; A[n+2] = -999;
    int mid = n % 2 ? n/2 + 1 : n/2;
    memset(dp,-1,sizeof(dp));
    for (int k = 1; k <= mid; k++) {
        cout << f(1,k,0) << ' ';
    }


    return 0;
}
	

