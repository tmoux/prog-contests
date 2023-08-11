#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

long long square(long long i) {return i*i;}
bool isPerfect(long long x) {
	long long root = (long long)round((sqrt(x)));
	return x == root * root;
}

void solve(long long x) 
{
	if (x == 0) {
		cout << "1 1\n";
		return;
	}
	if (x == 1) {
		cout << "-1\n";
		return;
	}
	int l = (int)sqrt(1000000000) + 2;
	for (int i = 1; i <= l; i++) {
		if (x % i != 0) continue;
		long a = x/i;
		long b = i;
		if (a == b || (a-b) % 2 != 0) continue;
		
		long k = (a-b)/2;
		long n = a-k;
		long m = n/k;
		if (n*n-(n/m)*(n/m)!=x) continue;
		cout << n << ' ' << m << '\n';
		return;
	}
	cout << "-1\n";
}

int main()
{
	int t; cin >> t;
	vector<long long> ts;
	for (int i = 0; i < t; i++) {
		long long xi; cin >> xi;
		ts.push_back(xi);
	}
	for (long long xi: ts) {
		solve(xi);
	}
	return 0;
}
