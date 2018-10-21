#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;

struct Sushi
{
	ll pos;
	ll nut;
};

const int maxn = 100005;
int N;
ll C;
Sushi A[maxn], B[maxn];
ll pfxA[maxn], pfxB[maxn];
ll maxA[maxn];
ll maxA2[maxn];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> N >> C;
	for (int i = 1; i <= N; i++) {
		ll xi, vi; cin >> xi >> vi;
		A[i] = {xi,vi};
		B[i] = {xi,vi};
	}
	B[N+1] = {C,0};
	for (int i = 1; i <= N; i++) {
		pfxA[i] = pfxA[i-1] + A[i].nut;
		pfxB[N-i+1] = pfxB[N-i+2] + B[N-i+1].nut;
	}
	//calculate max A
	for (int i = 1; i <= N; i++) {
		maxA[i] = max(maxA[i-1],pfxA[i]-A[i].pos);
		maxA2[i] = max(maxA2[i-1],pfxA[i]-2*A[i].pos);
		//cout << maxA[i] << '\n';
	}
	//calculate in O(n) maximum
	ll ans = 0;
	for (int j = N+1; j > 0; j--) {
		//cout << pfxB[j] << ' ' << (C - B[j].pos) << '\n';
		ll T = maxA[j-1] + pfxB[j] - 2*(C - B[j].pos);
		ans = max(ans,T);
		ll T2 = maxA2[j-1] + pfxB[j] - (C-B[j].pos);
		ans = max(ans,T2);
		/*
		for (int i = 0; i < j; i++) {
			ll OA = A[i].pos, OB = C - B[j].pos;
			ll d = OA + OB + min(OA,OB);
			ll nut = pfxA[i] + pfxB[j];
			ll T = nut - d;
			ans = max(ans,T);
			//cout << A[i].pos << ' ' << A[i].nut << '\n';
			//cout << B[j].pos << ' ' << B[j].nut << '\n';
			//cout << T << "\n\n";
		}
		*/
	}
	//output ans
	cout << ans << '\n';
	
	
	
	
	return 0;
}