#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, INF = 987654321;
int N, M, Q;
vector<int> ancestors[maxn];
int SZ;
list<pair<int,int>> bests[maxn];
auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) { return a.first > b.first; };

bool used[maxn], isBusy[maxn];
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> Q;
    for (int i = 0; i < M; i++) {
    	int s, e; cin >> s >> e;
    	ancestors[e].push_back(s);
    }
    SZ = 75; //each node will store at least the top SZ nodes
    //small queries are <= SZ - 1
    for (int i = 1; i <= N; i++) {
    	list<pair<int,int>>& li = bests[i];
    	li.push_back({0,i});
    	for (int j: ancestors[i]) {
    		list<pair<int,int>> add;
    		for (auto p: bests[j]) {
    			add.push_back({p.first+1,p.second});
    			if ((int)add.size() >= SZ) break;
    		}
    		li.merge(add,cmp);
    		for (auto it = li.begin(); it != li.end();) {
	    		if (used[it->second]) it = li.erase(it);
	    		else { used[it->second] = true;	++it; }
	    	}
	    	for (auto& p: li) used[p.second] = false; //reset for next one
	    	while ((int)li.size() > SZ) li.pop_back();
    	}
    	
    	
    	/*
    	cout << i << ": \n";
    	for (auto p: li) {
    		cout << p.first << ' ' << p.second << '\n';
    	}
    	cout << '\n';
    	*/
    }

	while (Q--) {
		int town, num; cin >> town >> num;
		vector<int> busy(num);
		for (int i = 0; i < num; i++) {
			cin >> busy[i];
			isBusy[busy[i]] = true;
		}
		if (num <= SZ - 1) {
			//answer will be in first SZ answers, if it exists
			bool found = false;
			for (auto& p: bests[town]) {
				if (!isBusy[p.second]) {
					found = true;
					cout << p.first << '\n';
					break;
				}
			}
			if (!found) {
				cout << -1 << '\n';
			}
		}
		else {
			//do normal O(N) DP
			//this only happens about sqrt(N) times
			vector<int> dp(N+1,-INF);
			for (int i = 1; i <= town; i++) {
				if (!isBusy[i]) dp[i] = 0;
				for (int j: ancestors[i]) {
					dp[i] = max(dp[i],dp[j]+1);
				}
			}
			int ans = dp[town] >= 0 ? dp[town] : -1;
			cout << ans << '\n';
		}
		//reset isBusy[] for next query
		for (int i: busy) isBusy[i] = false;
	}
    return 0;
}
