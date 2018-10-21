#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() 
{
	int n, m;
	cin >> n >> m;
	double minPrice = 999999999;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		double newPrice = (double) a / b * m;
		minPrice = min(minPrice, newPrice);
	}
	cout << setprecision(10) << minPrice << '\n';
	
	
	
	return 0;
}