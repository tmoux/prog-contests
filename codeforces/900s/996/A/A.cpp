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
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	int n; cin >> n;
	cout << n/100 + (n%100)/20 + (n%20)/10 + (n%10)/5 + (n%5)/1 << '\n';
	
	
	return 0;
}