#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;
ll N, ans = 0;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	N--;
	for (ll i = 1; i <= N; i <<= 1) {
		ans += ((N-i)/(2*i)+1)*i;
	}
	cout << ans << '\n';
	
	
	return 0;
}