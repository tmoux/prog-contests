#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line
{
    ll m, b;
    Line(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) {
        return m*x + b;
    }

    friend bool comp(Line& l1, Line& l2, Line& l) {
    	//order in deque: l1, l2, l
    	//true --> l2 is unnecessary
    	ll c1 = (l2.b-l1.b) * (l2.m-l.m);
    	ll c2 = (l2.b-l.b) * (l2.m-l1.m);
        return c1 >= c2;
    }
};

const int maxn = 1e5+5, maxp = 105;
const ll INF = 1e18;
int N, M, P; //N = # of hills, M = number of cats, P = number of feeders
int d[maxn];
ll A[maxn], pfx[maxn];
ll dp[maxp][maxn];

void dnc(int l, int r, int optl, int optr, int k) {
    if (l > r) return;
    int m = (l+r)>>1;
    pair<ll,int> best = {INF+1,-1};
    for (int j = optl; j <= min(m-1,optr); j++) {
        pair<ll,int> p = {dp[k-1][j] + (1LL*(m-j)*A[m] - (pfx[m]-pfx[j])),j};
        best = min(best,p);
    }
    int opt = best.second;
    dp[k][m] = best.first;
    if (opt == -1) {
        dnc(l,m-1,optl,optr,k);
        dnc(m+1,r,optl,optr,k);
        return;
    }
    dnc(l,m-1,optl,opt,k);
    dnc(m+1,r,opt,optr,k);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> P;
    for (int i = 2; i <= N; i++) {
    	cin >> d[i];
    	d[i] += d[i-1];
    }
    for (int i = 1; i <= M; i++) {
    	int hi, ti; cin >> hi >> ti;
    	A[i] = ti - d[hi];
    }
    sort(A+1,A+M+1);
    for (int i = 1; i <= M; i++) {
        pfx[i] = A[i] + pfx[i-1];    
        dp[1][i] = 1LL*i*A[i] - pfx[i];
    }
    for (int k = 2; k <= P; k++) {
        dnc(1,M,1,M,k);
        /* O(P*M^2)
        for (int i = 1; i <= M; i++) {
            dp[k][i] = INF;
            for (int j = 1; j <= i-1; j++) {
                dp[k][i] = min(dp[k][i], dp[k-1][j] + (1LL*(i-j)*A[i] - (pfx[i]-pfx[j])));      
            }
        }
        */
    }
    //output
    cout << dp[P][M] << '\n';

    return 0;
}
