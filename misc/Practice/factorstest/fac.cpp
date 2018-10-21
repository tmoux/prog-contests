#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

int getFactors(vector<pair<int,int>>& ps) {
    int ans = 1;
    for (pair<int,int> p: ps) {
        ans *= (p.second+1);
    }
    return ans;
}

void primeFactor(int n, map<int,int>& primes) {
	if (n == 1) return;
	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			while (n % i == 0) {
				primes[i]++;
				n /= i;
			}
			primeFactor(n,primes);
			return;
		}
	}
	primes[n]++;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	
	int max = 0, maxans;
	for (int i = 1; i <= 1000000; i++) {
		map<int,int> primes;
		vector<pair<int,int>> ps;
		primeFactor(i,primes);
		for (auto p: primes) {
			ps.push_back({p.first,p.second});
		}
		int ans = getFactors(ps);

		if (ans > max) {
			max = ans;
			maxans = i;
		}
	}

	printf("Maximum ans: %d with %d factors", maxans, max);
	
	return 0;
}
