#include <bits/stdc++.h>
using namespace std;
const int N=100000,LOGN=18;

int ph[N+9],Prime[N+9],primecnt;
long long g[N+9];
bool primeflag[N+9];
long long c(int l,int r) {
    long long res=0;
    while (l<=r) {
        int k=min(r/(r/l),r);
        res+=g[r/l]*(k-l+1);
        l=k+1;
    }
    return res;
}

long long dp[N+9][LOGN+9];
void solve(int l,int r,int L,int R,int u) {
    if (l>r) return ;
    int mid=l+r>>1,opt;
    long long val=c(R+1,mid);
    for (int i=min(R,mid);i>=L;i--) {
        val+=g[mid/i];
        long long h=dp[i-1][u-1]+val;
        if (dp[mid][u]>=h) dp[mid][u]=h,opt=i;
    }
    solve(l,mid-1,L,opt,u),solve(mid+1,r,opt,R,u);
}

void prework() {
    g[1]=1;
    for (int i=2;i<=N;i++) {
        if (!primeflag[i]) Prime[++primecnt]=i,ph[i]=i-1;
        g[i]=g[i-1]+ph[i];
        for (int j=1;j<=primecnt;j++) {
            if (i*Prime[j]>N) break;
            primeflag[i*Prime[j]]=1;
            if (i%Prime[j]==0) {
                ph[i*Prime[j]]=ph[i]*Prime[j];
                break;
            } else ph[i*Prime[j]]=ph[i]*(Prime[j]-1);
        }
    }
    memset(dp,0x3f,sizeof(dp)),dp[0][0]=0;
    for (int i=1;i<=LOGN;i++) solve(i,N,i,N,i);
}

int main() {
    prework();
    int t; scanf("%d",&t);
    while (t--) {
        int n,k; scanf("%d%d",&n,&k);
        if (k>LOGN) printf("%d\n",n);
        else printf("%lld\n",dp[n][k]);
    }
    return 0;
}
