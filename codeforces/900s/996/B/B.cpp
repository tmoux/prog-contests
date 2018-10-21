#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int A[maxn], n;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif

	cin >> n;
	int ans = 2000000000, idx;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		A[i] -= i;
		int ai;
		if (A[i] <= 0) ai = 0;
		else {
			ai = (A[i] % n ? A[i]/n+1 : A[i]/n);
		} 

		if (ai < ans) {
			ans = ai;
			idx = i;
		}

		//cout << i << ": " << ai << ' ' << ans << ' ' << idx << '\n';
	}

	cout << (idx+1) << '\n';	
	
	return 0;
}