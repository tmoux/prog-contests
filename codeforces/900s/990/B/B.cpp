#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, K;
int A[200005];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> K;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    int ans = n;
    int left = 0; 
    for (int i = 1; i < n; i++) {
        while (A[left] + K < A[i]) {
            left++;
        }
        while (A[left] < A[i] && A[i] <= A[left] + K) {
            ans--;
            left++;
        }
    }
    cout << ans << '\n';


    return 0;
}
	

