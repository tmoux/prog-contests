#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> vec;
    for (int i = 0; i < m; i++) {
        int f; cin >> f;
        vec.push_back(f);
    }
    sort(vec.begin(),vec.end());
    int ans = 999999999;
    for (int i = 0; i + n - 1 < m; i++) {
        ans = min(ans,vec[i+n-1]-vec[i]);
    }
    cout << ans << '\n';


    return 0;
}
	

