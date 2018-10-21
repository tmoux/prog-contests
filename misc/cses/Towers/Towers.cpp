#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;

multiset<int> ts;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int n; scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		int ki; scanf("%d",&ki);
		if (ts.size() == 0) {
			ts.insert(ki);
		}
		else if (ts.size() == 1) {
			if (ki >= *ts.begin()) {
				ts.insert(ki);
			}
			else {
				ts.erase(ts.begin());
				ts.insert(ki);
			}
		}
		else {
			if (*ts.rbegin() <= ki) {
				ts.insert(ki);
			}
			else {
				auto it = ts.upper_bound(ki);
				ts.erase(it);
				ts.insert(ki);
			}

		}
		/*
		for (int i: ts) {
			cout << i << ' ';
		}
		cout << '\n';
		*/
	}
	printf("%d\n",ts.size());
	
	
	return 0;
}