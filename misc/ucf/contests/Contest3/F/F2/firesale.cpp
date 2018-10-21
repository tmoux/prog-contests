#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;

int A[1000005];
int n, k;

int minn(const multiset<int>& a) {
    return *a.begin();
}
int maxx(const multiset<int>& a) {
    return *a.rbegin();
}
int range(int l, int r) {
    if (l == r) {
        return 1;
    }
    int mid = (l+r)/2;
    int ans = range(l,mid);
    ans = max(ans,range(mid+1,r));

    multiset<int> ns;
    int ll = mid, rr = mid;
    for (; ll >= l; ll--) {
        ns.insert(A[ll]);
        
        while (maxx(ns)-minn(ns) <= k && rr < r) {
            rr++;
            ns.insert(A[rr]);            
        }
        
        while (maxx(ns)-minn(ns) > k) {
            ns.erase(ns.find(A[rr]));
            rr--;
        }
        ans = max(ans,(int)ns.size());
        //cout << ll << ' ' << ns.size() << ' ' << ans << '\n';
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int ans = range(0,n-1);
    cout << ans << '\n';

    return 0;
}
	

