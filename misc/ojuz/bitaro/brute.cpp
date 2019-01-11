#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)

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
    SZ = sqrt(N) + 2; //each node will store at least the top SZ nodes
    //small queries are <= SZ - 1
	while (Q--) {
		int town, num; cin >> town >> num;
		vector<int> busy(num);
		for (int i = 0; i < num; i++) {
			cin >> busy[i];
			isBusy[busy[i]] = true;
		}
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
		//reset isBusy[] for next query
		for (int i: busy) isBusy[i] = false;
	}
    return 0;
}
