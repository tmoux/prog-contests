#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxk = 18, INF = 1e9;
string s;
int n, dp[maxk][26][1 << maxk];

int dist(char a, char b) {
    int aa = a-'A';
    int bb = b-'A';
	return min(abs(aa-bb),26-abs(aa-bb));
}

int f(int i, int prev, int mask) {
	if (mask + 1 == (1 << n)) return dp[i][mask] = 0;
	if (dp[i][mask] >= 0) return dp[i][mask];
	dp[i][mask] = INF;
	char curr = s[i];
	int moves = 0;
	for (int k = i + 1; k < n; k++) {
		if (!(mask & (1 << k))) {
			char next = s[k];
			dp[i][mask] = min(dp[i][mask],moves+dist(curr,next)+f(k,mask|(1<<k)));
		}
		else {
			moves++;
		}
	}
	moves = 1;
	for (int k = i - 1; k >= 0; k--) {
		if (!(mask & (1 << k))) {
			char next = s[k];
			dp[i][mask] = min(dp[i][mask],moves+dist(curr,next)+f(k,mask|(1<<k)));
		}
		else {
			moves++;
		}
	}
    return dp[i][mask];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while (true) {
    	cin >> s;
    	memset(dp,-1,sizeof(dp));
    	if (s == "0") break;
        for (char c: s) c -= 'A';
    	n = s.size();
        int ans = f(0,0);
    	cout << ans << '\n';
    }


    return 0;
}
