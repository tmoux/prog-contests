#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 100;
vector<int> vec;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n, d; cin >> n >> d;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		vec.push_back(a);
	}
	if (n == 1) {
		cout << "0\n";
		return 0;
	}
	int minremove = 999999;
	sort(vec.begin(),vec.end());
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (vec[j]-vec[i] <= d) {
				minremove = min(minremove,n-(j-i)-1);
			}
		}
	}
	cout << minremove << '\n';
	
	
	return 0;
}

