#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

int A[200001];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; cin >> n;
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		tot += A[i];
	}
	if (tot % 2 == 1) tot++;
	int half = tot/2;
	int curr = 0;
	for (int i = 1; i <= n; i++) {
		curr += A[i];
		if (curr >= half) {
			cout << i << '\n';
			return 0;
		}
	}
	
	
	return 0;
}