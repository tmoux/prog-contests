#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 4005;
int n, A[maxn], dp[maxn][maxn];
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    map<int,int> mp;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (mp.find(A[i]) == mp.end()) {
            mp[A[i]] = idx++;
        }
    }
    for (int i = 0; i < n; i++) {
        A[i] = mp[A[i]];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][A[j]] = max(dp[i][A[j]], 1 + dp[j][A[i]]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << '\n';


    return 0;
}
	

