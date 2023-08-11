#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
        int _;
    char s[105],num[26];
    for(scanf("%d",&_);_;--_)
    {
        memset(num,0,sizeof(num));
        scanf("%s",s);
        for(int i=0;s[i];++i) ++num[s[i]-'a'];
        string s1,s2;
        for(int i=0;i<26;i+=2) while(num[i]--) s1+='a'+i;
        for(int i=1;i<26;i+=2) while(num[i]--) s2+='a'+i;
        if(abs(s1.back()-s2.front())>1) cout<<s1<<s2<<"\n";
        else if(abs(s1.front()-s2.back())>1) cout<<s2<<s1<<"\n";
        else cout<<"No answer\n";
    }

    return 0;
}

