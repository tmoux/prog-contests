#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 505;
int N, M, K;
int dp[maxn][maxn];
int mn[maxn][maxn];
vector<int> intervals[maxn];



int f(int n, int k) {
	if (dp[n][k] != -1) {
		return dp[n][k];
	}	
	if (n == N) {
		return 0;
	}
	if (k == K) {
		return f(n+1,k) + 
	}
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	memset(dp,-1,sizeof(dp));
	memset(mn,-1,sizeof(mn));
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == '1') {
				intervals[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < intervals[i].size(); j++) {
			for (int k = j; k < intervals[i].size(); k++) {
				if (mn[i][k-j+1] == -1) {
					mn[i][k-j+1] = intervals[i][k]-intervals[i][k]+1;
				}
				else {
					mn[i][k-j+1] = min(mn[i][k-j+1],intervals[i][k]-intervals[i][k]+1);
				}
			}
		}
	}
	int ans = f(0,0);
	cout << ans << '\n';
	
	
	
	
	return 0;
}

