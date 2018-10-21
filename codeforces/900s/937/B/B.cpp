#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <math.h>
using namespace std;

typedef long long ll;


int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int p, y; cin >> p >> y;
	for (int i = y; i > max(y-305,p); i--) {
		bool works = true;
		for (int j = 2; j <= min((int)(sqrt(1000000000)),p); j++) {
			if (i % j == 0) {
				works = false;
				break;
			}
		}
		if (works) {
			cout << i << '\n';
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
	
	
	
	return 0;
}

