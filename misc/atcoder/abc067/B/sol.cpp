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
    int n, k; cin >> n >> k;
    vector<int> s;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        s.push_back(a);
    }
    int ans = 0;
    sort(s.begin(),s.end());
    for (int i = 0; i < k; i++) {
        ans += s[n-1-i];
    }
    cout << ans << '\n';

    return 0;
}
	

