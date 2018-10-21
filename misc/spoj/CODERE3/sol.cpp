#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, A[maxn];
int dp[2][maxn][maxn];
vector<int> T, S, lis, lds;

void solve() {
    cin >> n;
    //setup 
    T.resize(n+1);
    fill(T.begin(),T.end(),maxn);
    T[0] = 0;
    S.resize(n+1);
    fill(S.begin(),S.end(),maxn);
    S[0] = 0;
    lis.resize(n);
    lds.resize(n);
    //input
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(T.begin(),T.end(),A[i]);
        lis[i] = (int)distance(T.begin(),it); 
        *it = A[i]; 
    }
    reverse(A,A+n);
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(S.begin(),S.end(),A[i]);
        lds[n-1-i] = (int)distance(S.begin(),it); 
        *it = A[i]; 
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans,lis[i]+lds[i]-1);
    }
    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        //cout << i << ": " << lis[i] << ' ' << lds[i] << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) 
        solve();
    return 0;
}

