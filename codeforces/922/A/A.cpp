#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int x, y; cin >> x >> y;
	int copiesMade = y-1;
	//cout << copiesMade << '\n';
	if ((x-copiesMade) % 2 == 0 && copiesMade <= x && (y > 1 || x == 0)) {
		cout << "Yes\n";
		return 0;
	}
	cout << "No\n";
	return 0;
	
	
	return 0;
}