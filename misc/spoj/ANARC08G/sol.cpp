#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int adj[maxn][maxn];

void solve(int n,int t) {
	memset(adj,0,sizeof adj);
	int total = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> adj[i][j];
			total += adj[i][j];
		}
	}
	int rsum = 0;
	for (int i = 1; i <= n; i++) {
		int tot = 0;
		for (int j = 1; j <= n; j++) {
			tot += adj[i][j];
		}
		for (int j = 1; j <= n; j++) {
			tot -= adj[j][i];
		}
		if (tot > 0) rsum += tot;
	}
	cout << t << ". " << total << ' ' << rsum << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    for (int t = 1;;t++) {
    	int n; cin >> n;
    	if (!n) break;
    	solve(n,t);
    }


    return 0;
}