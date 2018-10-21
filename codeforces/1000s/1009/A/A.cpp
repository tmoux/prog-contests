#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> games(n);
    queue<int> wallet;
    for (int i = 0; i < n; i++) {
        cin >> games[i];    
    }
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        wallet.push(ai);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (wallet.size() == 0) continue;
        int f = wallet.front();
        if (f >= games[i]) {
            ans++;
            wallet.pop();
        }
    }
    cout << ans << '\n';


    return 0;
}
	

