#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	const int maxn = 101;
	int arr[maxn];
	int N;
	int totalsum = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		totalsum += arr[i];
	}
	sort(arr,arr+N);
	int maxdiff = totalsum;
	int part1 = 0, part2 = totalsum;
	for (int i = 0; i < N; i++) {
		part1 += arr[i];
		part2 -= arr[i];
		maxdiff = max(maxdiff,part2-part1);
	}
	cout << maxdiff << '\n';
	
	
	return 0;
}

