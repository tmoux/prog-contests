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
    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A.begin(),A.end());
    int curr = -1, curlen = 0, longest = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] != curr) {
            curr = A[i];
            curlen = 1;
        }
        else {
            curlen++;
        }
        longest = max(longest,curlen);
    }

    int ans = n - longest;
    cout << ans << '\n';


    return 0;
}
	

