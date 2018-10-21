#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int n, A, B, C, T;
int ti[1001];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> A >> B >> C >> T;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> ti[i];
	}
	int D = max(0,C-B);
	for (int i = 0; i < n; i++) {
		ans += (T-ti[i])*D+A;
	}
	cout << ans << '\n';
	
	return 0;
}