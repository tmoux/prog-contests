#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
	freopen("t1","w",stdout);
	int n, q; cin >> n >> q;
	printf("%d\n",n);
	for (int i = 2; i <= n; i++) {
		int r = (rand() % (i-1)) + 1;
		printf("%d %d\n",i,r);
	}
	cout << q << '\n';
	for (int i = 0; i < q; i++) {
		int t = rand() % 3 + 1;
		int v = rand() % n + 1;
		printf("%d %d\n",t,v);
	}
}