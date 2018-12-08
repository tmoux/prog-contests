#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005, maxk = 8;
int N, K;
ll r[2*maxn], C[3*maxn][3*maxn], dp[maxn][2*maxn][maxk];
const ll INF = 1e18;
//dp[s][i][k] = min cost starting at s, at pos i, with k doors left

void amin(ll& a, ll b) { a = min(a,b); }

void compute(int l, int r, int optl, int optr, int k, int s) {
	if (l > r) return;
	int mid = (l+r) >> 1;
	pair<ll,int> best = {INF,-1};
	for (int j = max(mid+1,optl); j <= optr; j++) {
		best = min(best,{dp[s][j][k-1] + C[mid][j-1],j});
	}
	dp[s][mid][k] = best.first;
	int opt = best.second;
	compute(l,mid-1,optl,opt,k,s);
	compute(mid+1,r,opt,optr,k,s);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("cbarn.in","r",stdin); freopen("cbarn.out","w",stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
    	cin >> r[i];
    	r[i+N] = r[i];
    }
    //compute costs
    for (int s = 1; s <= N; s++) {
    	for (int j = s+1; j <= s+N; j++) {
    		C[s][j] = C[s][j-1] + (j-s)*r[j];
    		//printf("C[%d][%d]: %d\n",s,j,C[s][j]);
    		C[s+N][j+N] = C[s][j];
    	}
    }
    
    for (int k = 1; k <= K; k++) {
    	for (int s = 1; s <= N; s++) {
    		if (k == 1) {
    			for (int i = s; i <= s+N-1; i++) {
    				dp[s][i][k] = C[i][s+N-1];
    			}
    		}
    		else {
    			compute(s,s+N-1,s,s+N-1,k,s);
    		}
    	}
    }

    ll ans = INF;
    for (int s = 1; s <= N; s++) {
    	//cout << dp[s][s][K] << '\n';
    	amin(ans,dp[s][s][K]);
    }
    cout << ans << '\n';
    return 0;
}