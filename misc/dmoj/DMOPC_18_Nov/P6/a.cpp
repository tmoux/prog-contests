#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int N, Q;
map<int,vector<int>> mp;
ll pref[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
    	cin >> pref[i];
    	mp[pref[i]].push_back(i);
    	pref[i] += pref[i-1];
    }

    while (Q--) {
    	int l, r; cin >> l >> r;
    	ll ans = 0;
    	for (auto& p: mp) {
    		auto l1 = lower_bound(all(mp[p.first]),l-1);
    		auto l2 = upper_bound(all(mp[p.first]),r+1);
    		if (l2 == mp[p.first].begin()) continue;
    		--l2;
    		int a = *l1 + 1;
    		int b = *l2 - 1;
    		
    	}
    }



    return 0;
}