#include<bits/stdc++.h>
using namespace std;
char s[200005];
int n,cs,ec,ncs,mc,mcs,me,fncs,fmen,fmcs,fmex,lncs,lmc,lmcs,lme;
void work()
{
	int i;
	scanf("%s",s+1);
	n=strlen(s+1);
	cs=ec=ncs=mc=mcs=me=fmcs=fmen=fmex=fncs=lmcs=lme=lmc=lncs=0;
	for(i=1;i<=n;i++)
	{
		if(s[i]=='W')ec++;
		if(s[i]=='S')ec--;
		if(s[i]=='A')cs--;
		if(s[i]=='D')cs++;
		if(ncs>cs)ncs=cs,fncs=i;
		if(ncs==cs)lncs=i;
		if(mc>ec)mc=ec,fmen=i;
		if(mc==ec)lmc=i;
		if(mcs<cs)mcs=cs,fmcs=i;
		if(mcs==cs)lmcs=i;
		if(me<ec)me=ec,fmex=i;
		if(me==ec)lme=i;
	}
	long long ans=1ll*(me-mc+1)*(mcs-ncs+1);
	if(1<-(lncs-fmcs)||1<-(lmcs-fncs))
		ans=min(1ll*(me-mc+1)*(mcs-ncs),ans);
	if(1<-(lmc-fmex)||1<-(lme-fmen))
		ans=min(1ll*(me-mc)*(mcs-ncs+1),ans);
	cout<<ans<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
		work();
	return 0;
}
