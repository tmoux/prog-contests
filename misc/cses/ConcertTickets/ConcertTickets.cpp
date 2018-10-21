#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int maxn = 200005;
int cust[maxn];
multiset<int> tickets;
int N, M;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int hi; cin >> hi;
		tickets.insert(hi);
	}
	for (int i = 0; i < M; i++) {
		int ti; cin >> ti;
		auto it = tickets.upper_bound(ti);
		if (it != tickets.begin()) {
			it--;
			cout << *it << '\n';
			tickets.erase(it);
		}
		else {
			cout << "-1\n";
		}
	}
	
	
	return 0;
}

