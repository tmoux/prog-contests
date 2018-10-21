#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<pair<int,int>> recs(n);
    for (int i = 0; i < n; i++) {
        int w, h; cin >> w >> h;
        recs[i] = {w,h};
    }

    recs[0].first = max(recs[0].first,recs[0].second);
    for (int i = 1; i < n; i++) {
        int prev = recs[i-1].first;
        if (recs[i].first <= prev && recs[i].second <= prev) {
            recs[i].first = max(recs[i].first,recs[i].second);
        }
        else if (recs[i].first <= prev && recs[i].second > prev) {
            recs[i].first = recs[i].first;
        }
        else if (recs[i].first > prev && recs[i].second <= prev) {
            recs[i].first = recs[i].second;
        }
        else {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';


    return 0;
}
	

