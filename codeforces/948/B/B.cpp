#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

int largestPrime(int n) {
	int lprime = 1;
	bool isPrime = true;
	for (int i = 2; i <= (int)(sqrt(n)); i++) {
		if (n % i == 0) {
			isPrime = false;
			while (n % i == 0) {
				n /= i;
			}
			lprime = max(i,largestPrime(n));
			break;
		}
	}
	if (isPrime) return n;
	return lprime;
}

int main()
{
	
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int x2; cin >> x2;
	auto start = steady_clock::now();
	int p2 = largestPrime(x2);
	int minans = 999999999;
	for (int i = x2-p2+1; i <= x2; i++) {
		if (largestPrime(i) != i) {
			int x0 = i-largestPrime(i)+1;
			minans = min(minans,x0);
		}
		
	}
	
	cout << minans << '\n';
	auto end = steady_clock::now();
	auto duration = duration_cast<milliseconds>(end-start);
	cout << fixed << setprecision(4) << duration.count()/1000. << " seconds" << '\n';
	//cout << largestPrime(8191) << '\n';
	
	return 0;
}

