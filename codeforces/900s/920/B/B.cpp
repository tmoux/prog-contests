#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        queue<pair<int,int>> q;
        for (int i = 0; i < n; i++) {
            int li, ri; cin >> li >> ri;
            q.push({li,ri});
        }
        int ans[1005];
        memset(ans,0,sizeof(ans));
        int time = 1;
        for (int i = 0; i < n; i++) {
            pair<int,int> p = q.front();
            time = max(time,p.first);
            if (time >= p.first && time <= p.second) {
                ans[i] = time;
                time++;
            }
            q.pop();
        }

        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }


    return 0;
}
	

