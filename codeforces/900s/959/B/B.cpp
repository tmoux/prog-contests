#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
const int INF = 2000000000;
const int maxn = 100001;
int n, k, m;
map<string,int> mapp;
int cost[maxn];

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> k >> m;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		mapp[s] = i;
	}
	for (int i = 1; i <= n; i++) {
		cin >> cost[i];
	}
	
	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		int minCost = INF;
		vector<int> vec;
		for (int j = 0; j < x; j++) {
			int xi; cin >> xi;
			vec.push_back(xi);
			minCost = min(minCost,cost[xi]);
		}
		//cout << i << ' ' << minCost << '\n';
		for (int j: vec) {
			cost[j] = minCost;
		}
	}
	
	long long ans = 0;
	for (int i = 0; i < m; i++) {
		string s; cin >> s;
		//cout << cost[mapp[s]] << '\n';
		ans += cost[mapp[s]];
	}
	cout << ans << '\n';
	
	
	return 0;
}

