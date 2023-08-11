#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int maxn = 100005;
const int maxWeight = 1000000000;
const int PRIME = 108023;
int n, m;


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> m;
	cout << PRIME << ' ' << PRIME << '\n';
	for (int i = 1; i <= n-1; i++) {
		int weight = 1;
		if (i == 1) {
			weight = PRIME-(n-2);
		}
		cout << i << ' ' << (i+1) << ' ' << weight << '\n';
	}
	int edgesLeft = m-(n-1);
	for (int i = 1; i <= n && edgesLeft > 0; i++) {
		for (int j = i+2; j <= n && edgesLeft > 0; j++) {
			cout << i << ' ' << j << ' ' << maxWeight << '\n';
			edgesLeft--;
		}
	}
	
	
	return 0;
}

