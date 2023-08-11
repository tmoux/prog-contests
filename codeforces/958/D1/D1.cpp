#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;

map<double,int> mapp;
const double EPS = 1e-9;
bool compare(double a, double b) {
	return (a-b) < EPS;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	int m; cin >> m;
	//int a = 1, b = 2, c = 3;
	char a[3],b[3],c[3];
	while (m--) {
		scanf("(%d+%d)/%d\n",a,b,c);
		//cout << a << ' ' << b << ' ' << c << '\n';
	}
	
	
	return 0;
}