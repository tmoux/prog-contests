#include<bits/stdc++.h>
using namespace std;
#define rep(v,l,r) for(int v=l;v<=r;++v)
#define upmin(x,y) x=min(x,y)
const int N=1e5+20,T=100;
int n, a[N],res=1e8,C;unordered_map<int,int> c;
void cal(int x) {c.clear();rep(i,1,n)upmin(res,n-(++c[a[i]-i*x]));}
signed main(){
    cin>>n; rep(i,1,n)cin>>a[i];
    rep(d,0,T)cal(d),cal(-d);
    rep(i,1,n){c.clear();
        rep(j,i+1,min(i+T*10,n))
        {
            C=a[j]-a[i];
            if(C%(j-i))continue;
            C/=j-i;
            upmin(res,n-(++c[C])-1);
        }
    }
    cout<<res;
}//kk
