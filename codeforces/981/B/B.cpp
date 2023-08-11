#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n;
    unordered_map<int,int> maxVal;
    for (int i = 0; i < n; i++) {
        int ai, xi; cin >> ai >> xi;
        maxVal[ai] = xi;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int ai, xi; cin >> ai >> xi;
        if (maxVal.find(ai) != maxVal.end()) {
            maxVal[ai] = max(maxVal[ai],xi);
        }
        else {
            maxVal[ai] = xi;
        }
    }

    //get answer
    ll ans = 0;
    for (auto p: maxVal) {
        //cout << p.first << ' ' << p.second << '\n';
        ans += (ll)p.second;
    }
    cout << ans << '\n';


    return 0;
}
	

