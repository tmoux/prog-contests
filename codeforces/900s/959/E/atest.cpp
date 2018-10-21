#include <iostream>
using namespace std;
int main()
{
    long long n,ans=0;
    scanf("%I64d",&n);
    n--;
    for (long long i=1;i<=n;i<<=1)
    ans+=((n-i)/(i<<1)+1)*i;
    printf("%I64d",ans);
}