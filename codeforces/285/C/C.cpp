#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

vector<int> s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        s.push_back(a);
    }
    sort(s.begin(),s.end());

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += abs(s[i-1]-i);
    }
    cout << ans << '\n';



    return 0;
}
	

