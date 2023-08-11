#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 100005;
int dp[maxn];
int nextNode[maxn];
int numApples[maxn];
int n;

int f(int n) {
	if (dp[n] != -1) {
		return dp[n];
	}
	return dp[n] = 1+f(nextNode[n]);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	memset(dp,-1,sizeof(dp));
	dp[1] = 0;
	
	for (int i = 2; i <= n; i++) {
		cin >> nextNode[i];
	}
	/*
	for (int i = 2; i <= n; i++) {
		cout << nextNode[i] << '\n';
	}
	*/
	
	for (int i = 1; i <= n; i++) {
		numApples[f(i)]++;
	}
	int totalnum = 0;
	for (int i = 0; i <= n; i++) {
		if (numApples[i] % 2 == 1) {
			totalnum++;
		}
	}
	cout << totalnum << '\n';
	
	
	
	
	return 0;
}

