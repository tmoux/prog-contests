#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isPerfect(int n) 
{
	int sum = 0;
	while (n > 0 && sum <= 10) {
		sum += n % 10;
		n /= 10;
	}
	if (sum == 10) {
		return true;
	}
	return false;
}

int main ()
{
	int k; cin >> k;
	int count = 1, start = 19;
	while (count < k) {
		start += 9;
		if (isPerfect(start)) {
			count++;
		}
	}
	cout << start << '\n';
	
	return 0;
}
