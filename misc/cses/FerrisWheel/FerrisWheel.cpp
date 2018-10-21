#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500005;
int k[maxn];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n, x; scanf("%d %d",&n,&x);
	for (int i = 0; i < n; i++) {
		scanf("%d",k+i);
	}
	sort(k,k+n);
	int right = n-1, left = 0, ans = 0;
	while (left <= right) {
		if (k[right] + k[left] <= x) {
			ans++;
			right--;
			left++;
		}
		else {
			ans++;
			right--;
		}
	}
	printf("%d\n",ans);
	
	
	return 0;
}

