#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MOD 1000000007
 
 
vector<long long> p;
vector<int> e;
int ans;
long long origN;
 
int fexp(int a,long long e)
{
	if(e==0) return 1;
	int tmp = fexp(a,e/2);
	tmp = (tmp*((long long)tmp))%MOD;
	if(e&1) tmp = (tmp*((long long)a))%MOD;
	return tmp;
}
 
long long gcd(long long a,long long b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
 
void dfs(int i,long long cdiv, long long sdiv, long long smult)
{
	if(i == p.size())
	{
		if(cdiv < origN)
			ans = (ans + fexp(2,cdiv)*((long long)((origN/(cdiv*sdiv))*smult)))%MOD;
		return;
	}
	for(int j=0;j<e[i];j++)
	{
		dfs(i+1,cdiv,sdiv*p[i],smult*(p[i]-1));
		cdiv *= p[i];
	}
	dfs(i+1,cdiv,sdiv,smult);
}
 
int main()
{
	long long N;
    freopen("gymnasts.in","r",stdin); freopen("gymnasts.out","w",stdout);
	cin >> N;
	origN = N;
	int i = 2;
	long long bound = N;
	for(i=2;i*((long long)i) < bound;i++)
		if(N%i == 0)
		{
			int mult = 0;
			while(N%i == 0)
			{
				mult++;
				N /= i;
			}
			p.push_back(i);
			e.push_back(mult);
		}
	if(i*((long long)i) == bound && N%i == 0)
	{
		int mult = 0;
		while(N%i == 0)
		{
			mult++;
			N /= i;
		}
		p.push_back(i);
		e.push_back(mult);
	}
	if(N > 1)
	{
		p.push_back(N);
		e.push_back(1);
	}
	dfs(0,1,1,1);
	ans = (ans + MOD - (origN - 1)%MOD)%MOD;
	ans = (ans+1)%MOD;
	cout << ans << '\n';
    return 0;
}



