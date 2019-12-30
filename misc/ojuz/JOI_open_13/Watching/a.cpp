#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int N, P, Q;
ll A[maxn];

int dp[maxn][maxn];
//[i-1'th one covered][# small used] = # of large needed
//

int jmpSmall[maxn], jmpBig[maxn];

int f(int i, int j) {
    if (i > N) return 0;
    int& res = dp[i][j];
    if (res != -1) return res;
    //take big one
    res = 1+f(jmpBig[i],j);
    if (j < P) res = min(res,f(jmpSmall[i],j+1));
    return res;
}

bool poss(ll w) {
    memset(dp,-1,sizeof dp);
    int pt = 0;
    for (int i = 1; i <= N; i++) {
        while (pt <= N && A[pt] < A[i]+w) pt++;
        jmpSmall[i] = pt;
    }
    pt = 0;
    for (int i = 1; i <= N; i++) {
        while (pt <= N && A[pt] < A[i]+2*w) pt++;
        jmpBig[i] = pt;
    }
    return f(1,0) <= Q;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> P >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    sort(A+1,A+N+1);
    ll lo = 0, hi = 1e9+9;
    while (lo + 1 < hi) {
        ll w = (lo+hi)/2;
        if (poss(w)) hi = w;
        else lo = w;
    }
    cout << hi << endl;
}

