#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, k, A[maxn];

bool isValid(int t) {
    int numNeed = 0;
    int curr = -1;
    for (int i = 0; i < n; i++) {
        if (curr == -1 || A[i] - curr > t) {
            numNeed++;
            curr = A[i];
        }
        
    }
    //cout << numNeed << '\n';
    return numNeed <= k;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    //special case
    if (A[0] == A[n-1]) {
        //all the same
        cout << 0 << '\n';
        return 0;
    }
    int c = 0;
    for (int i = 30; i >= 0; i--) {
        int tr = c + (1 << i);
        if (!isValid(tr)) {
            c = tr;
        }
        //cout << c << ' ' << (1 << i) << ' ' << isValid(tr) << '\n';
    }
    if (isValid(c)) {
        cout << c << '\n';
    }
    else {
        cout << (c+1) << '\n';
    }


    return 0;
}
	

