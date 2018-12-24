#include <iostream>
#include <algorithm>
using namespace std;
 
int N,K;
int A[10000];
int dp[10000];
 
int main()
{
    freopen("teamwork.in","r",stdin); freopen("teamwork.out","w",stdout);
	cin >> N >> K;
	for(int i=0;i<N;i++)
		cin >> A[i];
	dp[0] = A[0];
	for(int i=1;i<N;i++)
	{
		int mx = A[i];
		for(int j=i;j>=0 && i+1-j <= K; j--)
		{
			mx = max(mx, A[j]);
			if(j==0) dp[i] = max(dp[i],mx*(i+1-j));
			else dp[i] = max(dp[i],dp[j-1] + mx*(i+1-j));
		}
	}
	cout << dp[N-1] << '\n';
}
