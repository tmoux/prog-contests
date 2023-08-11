#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define Ys { putchar('1'); continue; }
#define No { putchar('0'); continue; }

using namespace std;

const int N=100010;

char s[N],t[N];
int ps[N],pt[N],ls[N],lt[N],q,n,m;

int main(){
	scanf("%s",s+1); n=strlen(s+1);
	scanf("%s",t+1); m=strlen(t+1);
	for(int i=1;i<=n;i++){
		ps[i]=ps[i-1]; ls[i]=ls[i-1];
		if(s[i]!='A') ps[i]++,ls[i]=i;
	}
	for(int i=1;i<=m;i++){
		pt[i]=pt[i-1]; lt[i]=lt[i-1];
		if(t[i]!='A') pt[i]++,lt[i]=i;
	}
	scanf("%d",&q);
	while(q--){
		int l,r,L,R;
		scanf("%d%d%d%d",&l,&r,&L,&R);
		if(ps[r]-ps[l-1]>pt[R]-pt[L-1]) No;
		if(ps[r]-ps[l-1]<pt[R]-pt[L-1]){
			if((pt[R]-pt[L-1])-(ps[r]-ps[l-1])&1) No;
			int t1=ls[r]>=l?r-ls[r]:r-l+1,t2=lt[R]>=L?R-lt[R]:R-L+1;
			if(ps[r]-ps[l-1]==0){
				if(t1<=t2) No; Ys;
			}
			if(t1<t2) No; Ys;
		}
		int t1=ls[r]>=l?r-ls[r]:r-l+1,t2=lt[R]>=L?R-lt[R]:R-L+1;
		if(t2>t1) No;
		if((t1-t2)%3==0) Ys;
		No;
	}
}
