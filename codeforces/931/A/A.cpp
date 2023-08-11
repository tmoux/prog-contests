#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int tired(int x) {
	x = abs(x);
	return (x)*(x+1)/2;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	int a, b;
	cin >> a >> b;
	int meeting = (a+b)/2;
	int ans = tired(meeting-a) + tired(meeting-b);
	cout << ans << '\n';
	
	
	return 0;
}

