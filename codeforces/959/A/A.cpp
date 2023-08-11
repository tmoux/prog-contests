#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int n;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	if (n == 1) {
		cout << "Ehab\n";
		return 0;
	}
	cout << ((n % 2 == 0) ? "Mahmoud":"Ehab") << '\n';
	
	
	return 0;
}

