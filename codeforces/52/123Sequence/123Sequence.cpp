#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
int n;
map<int,int> mapp;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	int maxnum = 0;
	for (int i = 0; i < n; i++) {
		int ai; cin >> ai;
		mapp[ai]++;
		maxnum = max(maxnum,mapp[ai]);
	}
	cout << (n-maxnum) << '\n';
	
	return 0;
}
