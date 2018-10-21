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
    vector<int> ans;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (i != 0 && A[i] == 1) {
            ans.push_back(A[i-1]);
        }
    }
    ans.push_back(A[n-1]);
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << ' ';


    return 0;
}
	

