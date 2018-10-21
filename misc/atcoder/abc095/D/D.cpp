#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int N;
ll C;

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> N >> C;
	ll maxNut = 0;
	deque<pair<ll,ll>> deq;
	while (N--) {
		ll xi, vi; 
		cin >> xi >> vi;
		deq.push_back({xi,vi});
	}
	
	
	
	return 0;
}