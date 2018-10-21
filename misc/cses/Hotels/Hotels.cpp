#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <list>
#include <map>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn = 200005;
vector<int> rooms;
map<int,set<int>> mapp;
int n, m;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int hi; cin >> hi;
		rooms.push_back(hi);
		mapp[hi].insert(i+1);
	}
	for (int i = 0; i < m; i++) {
		int ri; cin >> ri;
		if (map.count(ri) == 0) {
			cout << "0";
		}
		else {
			cout << *(map[ri].begin());
			map[ri].erase(map[ri].begin());
			map[]
		}
	}
	
	
	
	return 0;
}