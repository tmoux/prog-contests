#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef long long ll;
const int maxn = 100005;
multiset<ll> piles;
ll inserts[maxn];
ll temperature[maxn];
ll prefix[maxn];
ll tempprefix[maxn];
int N;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> N;
	int amtSubtract = 0;
	for (int i = 0; i < N; i++) {
		cin >> inserts[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> temperature[i];
	}
	prefix[0] = 0;
	for (int i = 1; i < N; i++) {
		prefix[i] = prefix[i-1] + temperature[i-1];
	}
	tempprefix[0] = temperature[0];
	for (int i = 1; i < N; i++) {
		tempprefix[i] = temperature[i] + tempprefix[i-1];
	}
	int running = 0;
	for (int i = 0; i < N; i++) {
		piles.insert(inserts[i]+prefix[i]);
		auto bound = piles.upper_bound(tempprefix[i]);
		ll total = 0;
		for (auto itr = piles.begin(); itr != bound; ++itr) {
			if (i == 0) {
				total += *itr;
			}
			else {
				total += (*itr - tempprefix[i-1]);
			}
		}
		piles.erase(piles.begin(),bound);
		total += temperature[i]*piles.size();
		cout << total << ' ';
	}
	cout << '\n';
	
	
	
	
	return 0;
}

