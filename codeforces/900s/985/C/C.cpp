#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxm = 100005;
int n, k, l;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> l;
    vector<ll> A(n*k);
    for (int i = 0; i < n*k; i++) cin >> A[i];
    sort(A.begin(),A.end());
    if (A[n-1] - A[0] > l) {
        cout << "0\n";
        return 0;
    }
    
    ll totalSum = 0;
    auto it = upper_bound(A.begin(),A.end(),A[0]+l);
    it--;
     

    return 0;
}
	

