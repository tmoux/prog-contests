#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;

const int INF = 2000000000;
int h, e, n;
struct Event
{
    int x, cost, hap;
};

Event events[110];

map<int,int> dp[105];

int f(int i, int j) {
    //i is pos, j is happiness
    if (dp[i].find(j) != dp[i].end()) return dp[i][j];
    if (j < 0) return INF;
    if (i == 0) return dp[i][j] = f(i+1,j - (events[i+1].x-events[i].x));
    if (i == n + 1) return 0;
    return dp[i][j] = min(f(i+1,j - (events[i+1].x-events[i].x)), events[i].cost + f(i+1,j - (events[i+1].x - events[i].x) + events[i].hap)); 
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> h >> e >> n;
    for (int i = 1; i <= n; i++) {
        int xi, ci, ai; cin >> xi >> ci >> ai;
        events[i] = {xi,ci,ai};
    }
    events[n+1] = {e,0,0};
    events[0] = {0,0,0};
    int ans = f(0,h);
    if (ans == INF) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }


    return 0;
}
	

