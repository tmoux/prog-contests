#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int maxidx = 1;
    int maxval = -1;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (A[i] > maxval) {
            maxval = A[i];
            maxidx = i + 1;
        }
    }
    sort(A,A+n);
    cout << maxidx << ' ' << A[n-2] << '\n';

    return 0;
}
	

