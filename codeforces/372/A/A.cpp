#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
    	cin >> A[i];
    }
    sort(A.begin(),A.end());
    int r = n/2;
    int ans = n;
    for (int i = 0; i < n/2; i++) {
    	while (true) {
    		if (A[i]*2 <= A[r]) {
    			ans--;
    			r++;
    			break;
    		}
    		else r++;
    		if (r == n) break;
    	}
    	if (r == n) break;
    }
    cout << ans << '\n';


    return 0;
}