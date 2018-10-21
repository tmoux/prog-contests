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
    int A[105];
    int maxelem = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        maxelem = max(maxelem,A[i]);
    }
    if (maxelem <= k) {
        cout << n << '\n';
        return 0;
    }
    int* left = A;
    while (*left <= k) left++;
    int* right = A+n-1;
    while (*right <= k) right--;
    int ans = (left - A) + ((A+n-1) - right);
    cout << ans << '\n';

    return 0; 
}
	

