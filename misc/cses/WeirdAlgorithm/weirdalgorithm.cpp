#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	ll n; cin >> n;
	while (n != 1) {
		cout << n << ' ';
		switch (n % 2) {
			case 0:
				n /= 2;
				break;
			case 1:
				n = n*3+1;
				break;
		}
	}
	cout << n << '\n';
	
	return 0;
}