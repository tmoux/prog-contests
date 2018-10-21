#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int A[maxn], n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int maxval = -1, maxidx;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (A[i] > maxval) {
            maxval = A[i];
            maxidx = i;
        }
    }
    A[maxidx] = (A[maxidx] == 1 ? 2 : 1);
    sort(A,A+n);
    for (int i = 0; i < n; i++) {
        cout << A[i] << ' ';
    }

    return 0;
}
	

