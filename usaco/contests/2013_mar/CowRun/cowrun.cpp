#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1010;
const ll INF = 1LL<<62;
int N, A[maxn];
ll dp[maxn][maxn][2];

ll f(int l, int r, bool isLeft) {
	ll& res = dp[l][r][isLeft];
	//cout << l << ' ' << r << ' ' << isLeft << ": " << curr << '\n';
	if (l == 1 && r == N) return res = 0LL;
	if (res >= 0) return res;
	int pos = isLeft ? A[l] : A[r];
	int cnt = N - (r - l) - 1;
	//cout << l << ' ' << r << ' ' << cnt << '\n';
	res = INF;
	if (r < N) {
		res = min(res,abs(pos-A[r+1])*cnt + f(l,r+1,0));
	}
	if (l > 1) {
		res = min(res,abs(pos-A[l-1])*cnt + f(l-1,r,1));
	}
	//cout << l << ' ' << r << ' ' << isLeft << ": " << res << '\n';
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("cowrun.in","r",stdin);
    freopen("cowrun.out","w",stdout);
    memset(dp,-1LL,sizeof dp);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
    A[++N] = 0;
    sort(A+1,A+N+1);

	for (int i = 1; i <= N; i++) {
		if (A[i] == 0) {
			ll ans = f(i,i,0);
			cout << ans << '\n';
		}
	}

    return 0;
}