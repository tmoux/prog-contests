#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> vec(2*n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> vec[i];
    }
    sort(vec.begin(),vec.end());
    ll minarea = 8e18;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            ll ar = (ll)(vec[2*n-1]-vec[n])*(vec[n-1]-vec[0]);
            minarea = min(minarea,ar);
        }
        else {
            ll ar = (ll)(vec[i+n-1]-vec[i])*(vec[2*n-1]-vec[0]);    
            minarea = min(minarea,ar);
        }
    }

    cout << minarea << '\n';

    return 0;
}
	

