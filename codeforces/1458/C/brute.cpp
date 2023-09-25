#include<bits/stdc++.h>
using namespace std;
#define s second
#define f first
char s[100008];
pair<int,int> x,y,z;
int t,n,m,i,j,a[1008][1008][3],b[1008][1008];
int main() {
    for(scanf("%d",&t); t--;) {
        for(x= {0,i=m=0},y= {0,1},z= {0,2},scanf("%d%*d",&n); i!=n; ++i)
            for(j=0; j!=n; scanf("%d",a[a[i][j][0]=i][a[i][j][1]=j]+2),
                    --a[i][j++][2]);
        for(scanf("%s",s+1); s[++m]; x.f+=n+(s[m]=='D')-(s[m]=='U'),
                y.f+=n+(s[m]=='R')-(s[m]=='L'),s[m]=='I'?(swap(y,z),0):0,
                s[m]=='C'?(swap(x,z),0):0);
        for(i=n; i--;)
            for(j=n; j--; b[(a[i][j][x.s]+x.f)%n][(a[i][j][y.s]+y.f)%n]
                    =(a[i][j][z.s]+z.f)%n);
        for(i=0; i!=n; printf("\n"),++i)
            for(j=0; j!=n; printf("%d ",b[i][j++]+1));
    }
    exit(0);
}
