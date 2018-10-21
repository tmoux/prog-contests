#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int lectures[maxn];
bool orig[maxn];
int maxTotal = 0;
int currTotal = 0;
int n, k;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
			cin >> lectures[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> orig[i];
		if (orig[i]) {
			currTotal += lectures[i];
		}
	}	
	
	for (int i = 0; i + k <= n; i++) {
		if (i == 0) {
			for (int j = i; j < k; j++) {
				if (!orig[j]) {
					currTotal += lectures[j];
				}
			}
		}
		else {
			if (!orig[i-1]) {
				currTotal -= lectures[i-1];
			}
			if (!orig[i+k-1]) {
				currTotal += lectures[i+k-1];
			}
		}
		maxTotal = max(maxTotal,currTotal);
	}
	cout << maxTotal << '\n';
	return 0;
}