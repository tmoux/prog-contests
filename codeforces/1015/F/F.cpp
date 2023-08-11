#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 205;
const int M = 1e9+7;
int N;
string s;
int dp[maxn][maxn][maxn];
//n = size, i = # of dominant left to place,
//j = # dominant placed before it
int f(int n, int i, int j) {
    if (n < 0 || i < 0) return 0;
    if (dp[n][i][j] >= 0) return dp[n][i][j];
    if (n == 0) {
        if (i == 0) return dp[n][i][j] = 1;
        return dp[n][i][j] = 0;
    }
    if (i == 0 || j == 0) return dp[n][i][j] = f(n-1,i,j+1);
    return dp[n][i][j] = (f(n-1,i,j+1) + f(n-1,i-1,j-1)) % M;
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //setup
    cin >> N >> s;
    if (2*N < s.size()) {
        cout << 0 << '\n';
        return 0;
    }
    memset(dp,-1,sizeof(dp));
    int lOwe = 0, rOwe = 0;
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') curr--;
        else {
            curr++;
            if (curr > 0) lOwe++;
        }
    }
    curr = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ')') curr--;
        else {
            curr++;
            if (curr > 0) rOwe++;
        }
    }
    //calc
    ll ans = 0;
    int net = curr; //net is how # ) - # (
    for (int i = 0; i < 2*N-s.size() + 1; i++) {
        int lsz = i;
        int rsz = 2*N-s.size() - i;
        for (int lAmt = 0; lAmt <= lsz; lAmt++) {
            int lNet = lAmt - (lsz - lAmt);
            int rNet = net - lNet;
            if ((rsz - rNet) % 2 != 0) continue;
            int rAmt = (rsz - rNet) / 2;
            if (lsz - lAmt >= lOwe && rsz - rAmt >= rOwe) {
                printf("Left: %d %d\nRight: %d %d\n\n",lsz,lAmt,rsz,rAmt);
                ans = (ans + ((ll)(f(lsz,lAmt,0)) * (ll)(f(rsz,rAmt,0)))%M)%M;
            }
        }
    }

    cout << net << ' ' << lOwe << ' ' << rOwe << '\n';

    cout << ans << '\n';


    return 0;
}
	

