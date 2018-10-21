#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
map<ll,set<int>> mapp;
ll A[150001];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	//input
	int n; cin >> n;
	int num = n;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		mapp[A[i]].insert(i);
	}
	//calculation
	//we can start doing the process for the smallest values, since they will never be returned to
	for (auto& p: mapp) {
		while (p.second.size() > 1) {
			auto it = p.second.begin();
			int f1 = *it++;
			int f2 = *it;
			A[f1] = -1;
			num--;
			A[f2] = p.first*2;
			mapp[p.first*2].insert(f2);
			p.second.erase(p.second.begin());
			p.second.erase(p.second.begin());
		}
	}
	
	//output
	cout << num << '\n';
	for (int i = 0; i < n; i++) {
		if (A[i] > 0) {
			cout << A[i] << ' ';
		}
	}
	cout << '\n';
	
	
	return 0;
}