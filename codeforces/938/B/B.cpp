#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int start1 = 1, start2 = 1000000;
set<int> prizes;

int main()
{
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int an;
		cin >> an;
		prizes.insert(an);
	}
	int numsec = 0;
	while (start1 < start2 && !prizes.empty()) {
		start1++;
		start2--;
		if (prizes.count(start1) != 0) {
			prizes.erase(start1);
		}
		if (prizes.count(start2) != 0) {
			prizes.erase(start2);
		}
		numsec++;
	}
	cout << numsec << '\n';
	
	
	return 0;
}