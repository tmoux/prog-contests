#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505;
int N, M, K;
int dp[maxn][maxn];
vector<int> intervals[maxn];

int getInterval(vector<int>& vec, int i, int j)
{
	if (j < i) {
		return 0;
	}
	return vec[j]-vec[i]+1;
}

int getWholeInterval(vector<int>& vec) {
	if (vec.size() == 0) {
		return 0;
	}
	return getInterval(vec,0,vec.size()-1);
}


int f(int n, int k) {
	if (dp[n][k] != -1) {
		return dp[n][k];
	}
	if (n == N) {
		return 0;
	}
	if (k == 0) {
		return f(n+1,k) + getWholeInterval(intervals[n]);
	}
	dp[n][k] = f(n+1,k) + getWholeInterval(intervals[n]);
	for (int i = 0; i < intervals[n].size(); i++) {
		for (int j = i; j < intervals[n].size(); j++) {
			int classesMissed = intervals[n].size()-(j-i+1);
			if (classesMissed <= k) {
				dp[n][k] = min(dp[n][k],f(n+1,k-classesMissed)+getInterval(intervals[n],i,j));	
			}
		}
	}
	//cout << n << ' ' << k << ' ' << dp[n][k] << '\n';
	return dp[n][k];
	
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	memset(dp,-1,sizeof(dp));
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == '1') {
				intervals[i].push_back(j);
			}
		}
	}
	int ans = f(0,K);
	cout << ans << '\n';
	
	
	
	
	return 0;
}

