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
    int A[100];
    int totalsum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        totalsum += A[i];
    }

    if (n == 1 || (n == 2 && A[1] == A[2])) {
        cout << "-1" << '\n';
        return 0;
    }
    
    cout << 1 << '\n';
    int minindex = 1;
    int mini = 999999;
    for (int i = 1; i <= n; i++) {
        if (A[i] < mini) {
            minindex = i;
            mini = A[i];
        }
    }
    cout << minindex << '\n';




    return 0;
}
	

