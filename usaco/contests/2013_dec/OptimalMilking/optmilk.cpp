#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 4e4+5, sq = sqrt(maxn) + 5;
int N, D, block, A[maxn], bucket[maxn], dp1[maxn], dp2[maxn], start[sq], len[sq];
pair<int,int> b1[sq], b2[sq];
int sqdp[sq][2];

int f(int i, bool r) { //r for restricted
    if (i > bucket[N]) return 0;
    if (sqdp[i][r] >= 0) return sqdp[i][r];
    if (r) {
        return sqdp[i][r] = max(b1[i].second + f(i+1,1),b2[i].second + f(i+1,0));
    }
    return sqdp[i][r] = max(b1[i].first + f(i+1,1),b2[i].first + f(i+1,0));
}

void updateBlock(int b) {
    int s = start[b], e = s + len[b] - 1;
    for (int i = e; i >= s; i--) {
        if (i == e) dp1[i] = A[i];
        else if (i == e-1) dp1[i] = max(A[i],A[i+1]);
        else dp1[i] = max(dp1[i+1],A[i]+dp1[i+2]);
    }
    b1[b].first = dp1[s];
    b1[b].second = len[b] == 1 ? 0 : dp1[s+1];
    for (int i = e-1; i >= s; i--) {
        if (i == e-1) dp2[i] = A[i];
        else if (i == e-2) dp2[i] = max(A[i],A[i+1]);
        else dp2[i] = max(dp2[i+1],A[i]+dp2[i+2]);
    }
    b2[b].first = dp2[s];
    b2[b].second = len[b] == 1 ? 0 : dp2[s+1];
    //cout << b << ' ' << b1[b].first << ' ' << b1[b].second << '\n';
    //cout << b << ' ' << b2[b].first << ' ' << b2[b].second << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("optmilk.in","r",stdin);
    freopen("optmilk.out","w",stdout);
    cin >> N >> D;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    //sqrt decomp
    int block = (int)(sqrt(N));
    for (int i = 1; i <= N; i++) {
        bucket[i] = (i-1)/block;
        len[bucket[i]]++;
        if (i == 1 || bucket[i-1] != bucket[i]) {
            start[bucket[i]] = i;
        }
    }
    for (int i = 0; i <= bucket[N]; i++) {
        updateBlock(i);
    }
    ll res = 0LL;
    for (int a = 1; a <= D; a++) { //do updates
        int i, x; cin >> i >> x;
        A[i] = x;
        updateBlock(bucket[i]);
        /*
        for (int j = 0; j <= bucket[N]; j++) {
            cout << j << ": " << b1[j].first << ' ' << b1[j].second << '\n';
            cout << j << ": " << b2[j].first << ' ' << b2[j].second << '\n';
        }
        */
        memset(sqdp,-1,sizeof sqdp);
        int ans = f(0,0);
        //cout << "Day " << a << ": " << ans << '\n';
        res += ans;
    }
    cout << res << '\n';
    /*
    for (int i = 1; i <= N; i++) {
        cout << i << ' ' << bucket[i] << ": " << dp2[i] << '\n';
    }
    */
        
    return 0;
}