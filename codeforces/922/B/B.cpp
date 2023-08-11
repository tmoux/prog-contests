#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int n;

bool isTriangle(int a, int b, int c) {
	if (c >= b && a + b > c && a + c > b && b + c > a && c <= n) {
		return true;
	}
	return false;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	int numtriples = 0;
	for (int a = 1; a <= n; a++) {
		for (int b = a; b <= n; b++) {
			int c = a^b^0;
			if (isTriangle(a,b,c)) {
				numtriples++;
				//cout << a << ' ' << b << ' ' << c << '\n';
			}
		}
	}
	cout << numtriples << '\n';
	
	return 0;
}